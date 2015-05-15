#pragma once

#include "Polygon.h"
#include "IShaderProgram.h"
#include "WaveFrontPolygon.h"
#include "Maze.h"
#include "libs\glm\glm.hpp"
#include "Animation.h"

class MazeWalker : PolygonWorldObject
{
private:
	WaveFrontPolygon* polygon;
	
	Maze *maze;

	glm::vec3 position;

	glm::vec3 target;

	Animation* movingAnimation;

public:
	void draw();

	MazeWalker(WaveFrontPolygon *polygon, IShaderProgram *program, Maze* maze);
};