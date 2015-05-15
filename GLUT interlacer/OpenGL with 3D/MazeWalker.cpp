#include "MazeWalker.h"
#include "CollisionDetection.h"
#include "World.h"


#include <cstdlib>
#include <Windows.h>


MazeWalker::MazeWalker(WaveFrontPolygon *polygon, IShaderProgram *program, Maze* maze) : 
								PolygonWorldObject(polygon, program) , maze(maze)
{
	World::getInstance()->objects.push_back(this);
	//Get list of wall positions
	std::vector< std::vector<bool> > mazeWallDef = maze->maze;
	double zOff = maze->zOffset;
	double xOff = maze->xOffset;
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
	srand(GetTickCount64());
	this->transformations.resize(1);
	do
	{
		int newPositionIndex = rand() % numElements;
		std::map<std::pair<int, int>, void*>::iterator it = positions.begin();
		std::advance(it, newPositionIndex);
		std::pair<int, int> startingPosition = it->first; //get the randomly selected element
		position = glm::vec3(startingPosition.second + xOff, 0.5, startingPosition.first + zOff);
	
		//Select adjacent position and set target
		target = getTargetForPosition(position);
	
		//Create transformation
		movingAnimation = createAnimation(position, target);
		this->transformations[0] = movingAnimation;
	}
	while (CollisionDetection::objectCollidesWithObjects(this));
	
}

glm::vec3 MazeWalker::getTargetForPosition(glm::vec3 position)
{
	return position + glm::vec3(0, 1, 0);
}

Animation* MazeWalker::createAnimation(glm::vec3 position, glm::vec3 target)
{
	Vertex4 baseValues = { position.x, position.y, position.z, 0 };
	Vertex4 aniValues = { (target.x - position.x) / 10, (target.y - position.y) / 10, (target.z - position.z) / 10, 0 };
	Animation *ani = new Animation(TRANSLATE, baseValues, 1000, aniValues);
	return ani;
}


void MazeWalker::draw()
{
	//Check for collisions
		
		//Get adjacent position

		//Calculate path to target

		//Update transformation
	// Check if it made it to target
		
	//Snap to target
	PolygonWorldObject::draw();
}