#include "MazeWalker.h"

MazeWalker::MazeWalker(WaveFrontPolygon *polygon, IShaderProgram *program, Maze* maze) : 
								PolygonWorldObject(polygon, program) , maze(maze)
{
	//Get list of wall positions

	//Select random position

	//Select adjacent position and set target

	//Calculate path to target

	//Create transformation
}

void MazeWalker::draw()
{
	//Check for collisions
		
		//Get adjacent position

		//Calculate path to target

		//Update transformation
	PolygonWorldObject::draw();
}