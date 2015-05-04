#pragma once

#include "TangentPolygonWorldObject.h"
#include "TangentWaveFrontPolygon.h"
#include "GraphicsUtil.h"

#include <string>
#include <vector>
#include <map>
#include <utility>

//! A class used to represent a maze with walls.
/*!
	Handles loading the maze from file and rendering it.
*/
class Maze
{

public:
	//! Constructor for the maze object. Reads a maze from file and creates
	//! a representation of it.
	//! @param mazeFile The path to the file describing the maze.
	//! @param wall The polygon that will be used to render a wall unit.
	Maze(std::string mazeFile, TangentWaveFrontPolygon* wall);

	//! Gets the list of polygons the camera can see and draws it.
	void render(Vertex3 position, double angle, double fov);

private:
	//! The width of the wall
	static const int WALL_WIDTH = 1;

	//! The depth of the wall
	static const int WALL_DEPTH = 1;

	//! The hight of the wall
	static const int WALL_HEIGHT = 1;

	//! The number of rows
	int rows;

	//! The number of columns
	int columns;

	//! The X offset to draw the maze
	double xOffset;

	//! The Z offset to draw the maze
	double zOffset;

	//! The object that is drawn if seen 
	TangentWaveFrontPolygon* wall;

	//! The 2D vector representing the maze
	std::vector<std::vector<bool>> maze;

	//! The walls in the map
	std::map<std::pair<int, int>, TangentPolygonWorldObject*> walls;


	
};