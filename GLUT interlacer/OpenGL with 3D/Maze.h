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
	Handles loading the maze from file and rendering it. Rendering of the maze uses raycasting in order to only send to openGL
	the walls that are currently within the user's field of view.
*/
class Maze
{

public:
	//! Constructor for the maze object. Reads a maze from file and creates
	//! a representation of it.
	/*!
		Pseudocode:
		@verbatim
			vector<vector<bool> boolMaze loadMaze(file)
			for (i < rows)
				for (j < columns)
					if (boolMaze[i][j])
						walls.Add([i, j], wallPolygon) //Add wall for coordinate key
		@endverbatim
	*/
	//! @param mazeFile The path to the file describing the maze.
	//! @param wall The polygon that will be used to render a wall unit.
	Maze(std::string mazeFile, TangentWaveFrontPolygon* wall);

	//! Gets the list of polygons the camera can see and draws it.
	//! @param position The position of the camera in the world.
	//! @param angle The angle of the camera
	//! @param fov The field of view.
	void render(Vertex3 position, double angle, double fov);

	//! Checks if a given object collides with any wall in the maze.
	//! @param object A pointer to the object to be checked.
	//! @return True if the object collides, else false.
	bool collides(WorldObject* object);

	//! The X offset to draw the maze
	double xOffset;

	//! The Z offset to draw the maze
	double zOffset;

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

	
	//! The object that is drawn if seen 
	TangentWaveFrontPolygon* wall;

	//! The 2D vector representing the maze
	std::vector<std::vector<bool>> maze;

	//! The walls in the map
	std::map<std::pair<int, int>, TangentPolygonWorldObject*> walls;

	//! Uses ray casting to identify walls that are visible to the camera.
	/*! Pseudocode:
		@verbatim
		for (each ray in fov)
			while (ray within bounds)
				extend ray using constant x increment
				if (ray(x,z).isWall())
					visibleWalls.Add(walls[x,z]) //Add to visible wall list
			while (ray within bounds)
				extend ray using constant z increment
				if (ray(x,z).isWall())
					visibleWalls.Add(walls[x,z])
		return visibleWalls			
		@endverbatim
	*/
	//! @param position The position of the camera in the world.
	//! @param angle The angle of the camera
	//! @param fov The field of view.
	//! @return A list of walls in view of the camera.
	std::vector<TangentPolygonWorldObject*> rayCast(Vertex3 position, double angle, double fov);
	
};