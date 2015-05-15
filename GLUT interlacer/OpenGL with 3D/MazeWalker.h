#pragma once

#include "Polygon.h"
#include "IShaderProgram.h"
#include "WaveFrontPolygon.h"
#include "Maze.h"
#include "libs\glm\glm.hpp"

class MazeWalker : PolygonWorldObject
{
private:
	WaveFrontPolygon* polygon;
	
	Maze *maze;

	glm::vec3 target;

public:
	void draw();

	MazeWalker(WaveFrontPolygon *polygon, IShaderProgram *program);
};