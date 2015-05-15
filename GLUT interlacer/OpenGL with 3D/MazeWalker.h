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

	WaveFrontPolygon *polygon;
	
	Maze *maze;

	std::map<std::pair<int, int>, void*> positions;

	glm::vec3 position;

	glm::vec3 target;

	Animation* movingAnimation;

public:
	void draw();

	MazeWalker(WaveFrontPolygon *polygon, IShaderProgram *program, Maze* maze);
};