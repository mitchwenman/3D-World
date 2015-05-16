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
	// Get position in maze
	double zOff = maze->zOffset;
	double xOff = maze->xOffset;
	std::pair<int, int> mazePos(position.x - xOff, position.z - zOff);
	std::pair<int, int> mazeCoord(mazePos.second, mazePos.first); //Z axis is rows
	
	std::vector<std::pair<int, int>> possibleTargets;
	//Top left
	std::pair<int, int> topLeft(mazeCoord.first - 1, mazeCoord.second - 1);
	if (positions.count(topLeft) == 1)
		possibleTargets.push_back(topLeft);
	//Above
	std::pair<int, int> above(mazeCoord.first - 1, mazeCoord.second);
	if (positions.count(above) == 1)
		possibleTargets.push_back(above);
	//Top right
	std::pair<int, int> topRight(mazeCoord.first - 1, mazeCoord.second + 1);
	if (positions.count(topRight) == 1)
		possibleTargets.push_back(topRight);
	//Right
	std::pair<int, int> right(mazeCoord.first, mazeCoord.second + 1);
	if (positions.count(right) == 1)
		possibleTargets.push_back(right);
	//Bottom right
	std::pair<int, int> bottomRight(mazeCoord.first + 1, mazeCoord.second + 1);
	if (positions.count(bottomRight) == 1)
		possibleTargets.push_back(bottomRight);
	//Bottom
	std::pair<int, int> bottom(mazeCoord.first + 1, mazeCoord.second);
	if (positions.count(bottom) == 1)
		possibleTargets.push_back(bottom);
	//Bottom left
	std::pair<int, int> bottomLeft(mazeCoord.first + 1, mazeCoord.second - 1);
	if (positions.count(bottomLeft) == 1)
		possibleTargets.push_back(bottomLeft);
	//Left
	std::pair<int, int> left(mazeCoord.first, mazeCoord.second - 1);
	if (positions.count(left) == 1)
		possibleTargets.push_back(left);

	int nextTargetIndex = rand() % possibleTargets.size();
	std::pair<int, int> nextTargetCoord = possibleTargets[nextTargetIndex];
	glm::vec3 nextTarget = glm::vec3(nextTargetCoord.second + xOff, 0.5, nextTargetCoord.first + zOff);
	return nextTarget;
}

Animation* MazeWalker::createAnimation(glm::vec3 position, glm::vec3 target)
{
	Vertex4 baseValues = { position.x, position.y, position.z, 0 };
	Vertex4 aniValues = { (target.x - position.x) / 20, (target.y - position.y) / 20, (target.z - position.z) / 20, 0 };
	Animation *ani = new Animation(TRANSLATE, baseValues, 50, aniValues);
	return ani;
}

bool MazeWalker::isAtTarget(glm::vec3 position, glm::vec3 target)
{
	double xDiff = abs(target.x - position.x);
	double zDiff = abs(target.z - position.z);
	return xDiff < 0.05 && zDiff < 0.05;
}

void MazeWalker::draw()
{
	position = glm::vec3(movingAnimation->values.x, movingAnimation->values.y, movingAnimation->values.z);
	//Check for collisions
	if (false) 
	{
		//Get adjacent position

		//Calculate path to target

		//Update transformation
	}	
	
	//Snap to target if close to target
	else if (isAtTarget(position, target))
	{
		position = target;
		target = getTargetForPosition(position);
		delete(movingAnimation);
		movingAnimation = createAnimation(position, target);
		transformations[0] = movingAnimation;

	}
	PolygonWorldObject::draw();
}