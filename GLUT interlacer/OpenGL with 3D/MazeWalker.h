#pragma once

#include "Polygon.h"
#include "IShaderProgram.h"
#include "WaveFrontPolygon.h"
#include "Maze.h"
#include "libs\glm\glm.hpp"
#include "Animation.h"

#include <vector>
#include <map>
#include <utility>

class MazeWalker : public PolygonWorldObject
{
private:

	Maze *maze;

	std::map<std::pair<int, int>, void*> positions;

	glm::vec3 position;

	glm::vec3 target;

	Animation* movingAnimation;

	glm::vec3 getTargetForPosition(glm::vec3 position);

	Animation* createAnimation(glm::vec3 position, glm::vec3 target);

	bool isAtTarget(glm::vec3 position, glm::vec3 target);

public:
	void draw();

	MazeWalker(WaveFrontPolygon *polygon, IShaderProgram *program, Maze* maze);
};