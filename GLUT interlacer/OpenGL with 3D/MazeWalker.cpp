#include "MazeWalker.h"

#include <cstdlib>

MazeWalker::MazeWalker(WaveFrontPolygon *polygon, IShaderProgram *program, Maze* maze) : 
								PolygonWorldObject(polygon, program) , maze(maze)
{
	//Get list of wall positions
	std::vector< std::vector<bool> > mazeWallDef = maze->maze;
	for (int z = 0; z < maze->getRows(); z++)
	{
		for (int x = 0; x < maze->getColumns(); x++)
		{
			if (!mazeWallDef[z][x])
			{
				std::pair<int, int> coords(z, x);
				positions[coords] = NULL; //using a map as a set
			}
		}
	}
	//Select random position
	int numElements = positions.size();
	int newPositionIndex = rand() % numElements;
	std::map<std::pair<int, int>, void*>::iterator it = positions.begin();
	std::advance(it, newPositionIndex);
	std::pair<int, int> startingPosition = it->first;
	position = glm::vec3(startingPosition.second, 0.5, startingPosition.first);
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