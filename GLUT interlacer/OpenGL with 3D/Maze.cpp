#include "Maze.h"
#include "SpecularNormalMap.h"
#include "Transformation.h"
#include "GraphicsSettings.h"
#include "Camera.h"
#include "MazeReader.h"
#include "GraphicsUtil.h"
#include <math.h>


Maze::Maze(std::string mazeFile, TangentWaveFrontPolygon* wall) : wall(wall), xOffset(-3.5), zOffset(-2.5)
{
	this->maze = MazeReader::readFromFile(mazeFile);
	//Temporary maze for testing purposes
	rows = this->maze.size();
	if (rows > 0)
		columns = this->maze[0].size();
	else 
		columns = 0;

	// Create objects from all walls
	IShaderProgram *program = new SpecularNormalMap("wood_floor.bmp", "wood_normal.bmp");
	//For each wall, create object with translations, add to wall map
	double yoffset = WALL_HEIGHT / 2.0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (maze[i][j]) //If there's a wall
			{
				//Create transformation
				Vertex4 trans = { j + xOffset, yoffset, i + zOffset, 0 };
				Transformation *translate = new Transformation(TRANSLATE, trans);
				//Create object
				TangentPolygonWorldObject *poly = new TangentPolygonWorldObject(this->wall, program);
				poly->transformations.push_back(translate);
				//Add to map
				std::pair<int, int> position = std::pair<int, int>(i, j);
				walls[position] = poly;
			}
		}
	}
}

void Maze::render(Vertex3 position, double angle, double fov)
{	
	const double PI = std::atan(1.0) * 4;
	//Find position in grid
	int posx = position.x - xOffset;
	int posz = position.z - zOffset;
	//Adjust angle - cam angle is 0 at PI / 2
	double viewAngle = fmod(2 * PI - angle + PI / 2, 2 * PI);
	//Ray cast from right to left - check horizontal intersections then vertical
	//Move to next ray when: outside grid or wall is found.
	//If wall found on horizontal and vertical - compare distances
	double fovInRadians = GraphicsUtil::degreesToRadians(fov);
	double leftArc = viewAngle + (fovInRadians / 2);
	double rightArc = viewAngle - (fovInRadians / 2);
	double angleIncrement = (leftArc - rightArc) / 60;
	std::map<std::pair<int, int>, TangentPolygonWorldObject*> visibleWalls;
	for (double ray = rightArc; ray <= leftArc; ray += angleIncrement)
	{
		int xHIntercept = -1;
		int zHIntercept = -1;
		int xH = posx;
		int zH = posz;
		int zDiff = (ray < PI) ? -1 : 1; //If ray is going down need to increase z
		//Check for horizontal intersections
		double xIncrease = WALL_WIDTH / tan(ray);
		int scale = 1;
		while (xH < columns && xH >= 0 &&
				zH < rows && zH >= 0)
		{			
			xH += scale * xIncrease;
			zH += zDiff;
			if (walls.count(std::pair<int, int>(zH, xH)) == 1) //Check for a wall
			{
				xHIntercept = xH;
				zHIntercept = zH;
				break;
			}
			scale++;
		}
				
		//Check for vertical intersections
		int xVIntercept = -1;
		int zVIntercept = -1;
		int xV = posx;
		int zV = posz;
		int xDiff = (ray < PI / 2 || ray > 3 * PI / 2) ? 1 : -1;
		double zIncrease = WALL_WIDTH * tan(ray);
		scale = 1;
		while (xV < columns && xV >= 0 &&
				zV < rows && zV >= 0)
		{
			xV += xDiff;
			zV += scale * zIncrease;
			if (walls.count(std::pair<int, int>(zV, xV)) == 1)
			{
				xVIntercept = xV;
				zVIntercept = zV;
				break;
			}
			scale++;
		}
		//Compare distance
		if (xVIntercept == -1 && xHIntercept != -1) //No vertical intercept
		{
			std::pair<int, int> coords(zHIntercept, xHIntercept);
			visibleWalls[coords] = walls[coords];
		} else if (xHIntercept == -1 && xVIntercept != -1) //No horizontal intercept
		{
			std::pair<int, int> coords(zVIntercept, xVIntercept);
			visibleWalls[coords] = walls[coords];
		} else if (xHIntercept != -1 && xVIntercept != -1)
		{
			int xHDist = xHIntercept - posx;
			int zHDist = zHIntercept - posz;
			double hDistance = sqrt((double)xHDist * xHDist + zHDist * zHDist);
			int xVDist = xVIntercept - posx;
			int zVDist = zVIntercept - posz;
			double vDistance = sqrt((double)xVDist * xVDist + zVDist * zVDist);
			std::pair<int, int> coords;
			if (hDistance < vDistance)
			{
				coords = std::pair<int, int>(zHIntercept, xHIntercept);
			} else
			{
				coords = std::pair<int, int>(zVIntercept, xVIntercept);
			}
			visibleWalls[coords] = walls[coords];
		}
			

	}
	

	GraphicsSettings *gset = GraphicsSettings::getSingleton();
	gset->resetModelView();
	Camera::getSingleton()->setCamera();
	for (std::map<std::pair<int, int>, TangentPolygonWorldObject*>::iterator it = visibleWalls.begin(); it != visibleWalls.end(); it++)
	{
		TangentPolygonWorldObject *wallObject = it->second;
		wallObject->draw();
		gset->resetModelView();
		Camera::getSingleton()->setCamera();

	}
}