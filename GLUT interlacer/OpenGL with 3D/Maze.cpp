#include "Maze.h"
#include "SpecularNormalMap.h"
#include "Transformation.h"
#include "GraphicsSettings.h"
#include "Camera.h"
#include "MazeReader.h"
#include "GraphicsUtil.h"
#include <math.h>


Maze::Maze(std::string mazeFile, TangentWaveFrontPolygon* wall) : wall(wall), xOffset(-1.5), zOffset(-2.5)
{
	this->maze = MazeReader::readFromFile(mazeFile);
	//Temporary maze for testing purposes
	rows = this->maze.size();
	if (rows > 0)
		columns = this->maze[0].size();
	else 
		columns = 0;

	// Create objects from all walls
	IShaderProgram *program = new SpecularNormalMap("brickwork-texture.bmp", "brickwork-normal.bmp");
	//For each wall, create object with translations, add to wall map
	double yoffset = WALL_HEIGHT / 2.0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (maze[i][j]) //If there's a wall
			{
				//Create transformation
				Vertex4 trans = { j + xOffset, yoffset, i + zOffset , 0 };
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
	std::vector<TangentPolygonWorldObject *> visibleWallList = this->rayCast(position, angle, fov);
	GraphicsSettings *gset = GraphicsSettings::getSingleton();
	gset->resetModelView();
	Camera *cam = Camera::getSingleton();
	cam->setCamera();
	for (std::vector<TangentPolygonWorldObject *>::iterator it = visibleWallList.begin();
		it != visibleWallList.end(); it++)
	{
		(*it)->draw();
		gset->resetModelView();
		cam->setCamera();
	}
}

std::vector<TangentPolygonWorldObject*> Maze::rayCast(Vertex3 position, double angle, double fov)
{
	const double PI = std::atan(1.0) * 4;
	//Find position in grid
	double posx = position.x - xOffset + WALL_WIDTH / 2.0; 
	double posz = position.z - zOffset + WALL_DEPTH / 2.0; //Blocks defined around origin. So each block occupies -.5 to .5 in space.
														   //Easier to offset position than take this into account when ray casting.
	std::map<std::pair<int, int>, TangentPolygonWorldObject*> visibleWalls;
	// Check bounds

		//Adjust angle - cam angle is 0 at PI / 2
		double viewAngle = fmod(2 * PI - angle + PI / 2, 2 * PI);
		//Ray cast from right to left - check horizontal intersections then vertical
		//Move to next ray when: outside grid or wall is found.
		//If wall found on horizontal and vertical - compare distances
		double fovInRadians = GraphicsUtil::degreesToRadians(fov);
		double leftArc = viewAngle + (fovInRadians / 2); //Create ray arc
		double rightArc = viewAngle - (fovInRadians / 2);
		double angleIncrement =  (leftArc - rightArc) / fov;

		for (double ray = rightArc; ray <= leftArc; ray += angleIncrement)
		{
			double modRay = fmod(ray + 2 * PI, 2 * PI); //Get rid of negatives
			double rayCalc = modRay;
			//Adjust ray if outside of first quadrant
			//Take care of the sign later
			if (rayCalc < PI && rayCalc > PI / 2)
				rayCalc = PI / 2 - (rayCalc - PI / 2);
			else if (rayCalc < 3 * PI / 2 && rayCalc > PI)
				rayCalc = rayCalc - PI;
			else if (rayCalc > 3 * PI / 2)
				rayCalc = 2 * PI - ray;

			int xHIntercept = -1;
			int zHIntercept = -1;
			double xH = posx;
			double zH = posz;
			double xIncrease = .5 / tan(rayCalc); // adj = opp / tan(x)
			if (modRay < 3 * PI / 2 && modRay >= PI / 2) xIncrease *= -1; // Q2/Q3 - going left
			double zDiff = (modRay < PI) ? -.5 : .5; //If ray is going down need to increase z
			//Check for horizontal intersections
			int scale = 1;
			while (abs(zH - posz) < rows * 1.5 &&
					abs(xH - posx) < columns * 1.5)
			{			
				xH = posx + scale * xIncrease;
				zH += zDiff;
				if (xH < columns && xH >= 0 &&
					zH < rows && zH >= 0)
				{
					if (walls.count(std::pair<int, int>((int)zH, (int)xH)) == 1) //Check for a wall
					{						
						xHIntercept = (int)xH;
						zHIntercept = (int)zH;
						break;
					}
				}
				scale++;

			}
				
			//Check for vertical intersections
			int xVIntercept = -1;
			int zVIntercept = -1;
			double xV = posx;
			double zV = posz;
			double xDiff = (modRay < PI / 2 || modRay > 3 * PI / 2) ? .5 : -.5; // Q2/Q3 going left
			double zIncrease = .5 * tan(rayCalc); // opp = adj * tan(x)
			if (modRay < PI) zIncrease *= -1;
			scale = 1;
			while (abs(xV - posx) < columns * 1.5 &&
					abs(zV - posz) < rows * 1.5)
			{
				xV = posx + scale * xDiff;
				zV = posz + scale * zIncrease;
				if (xV < columns && xV >= 0 &&
					zV < rows && zV >= 0)
				{
					if (walls.count(std::pair<int, int>((int)zV, (int)xV)) == 1)
					{				
						xVIntercept = (int)xV;
						zVIntercept = (int)zV;
						break; 
					}
				}
				scale++;
			}
		
			if (xVIntercept == -1 && xHIntercept != -1) //No vertical intercept
			{
				std::pair<int, int> coords(zHIntercept, xHIntercept);
				visibleWalls[coords] = walls[coords];
			} else if (xHIntercept == -1 && xVIntercept != -1) //No horizontal intercept
			{
				std::pair<int, int> coords(zVIntercept, xVIntercept);
				visibleWalls[coords] = walls[coords];
			} else if (xHIntercept != -1 && xVIntercept != -1) //Compare distance
			{
				double xHDist = xHIntercept - posx;
				double zHDist = zHIntercept - posz;
				double hDistance = sqrt(xHDist * xHDist + zHDist * zHDist);
				double xVDist = xVIntercept - posx;
				double zVDist = zVIntercept - posz;
				double vDistance = sqrt(xVDist * xVDist + zVDist * zVDist);
				std::pair<int, int> coords;
				if (hDistance < vDistance)
				{
					coords = std::pair<int, int>(zHIntercept, xHIntercept);
					visibleWalls[coords] = walls[coords];
				} else if (vDistance < hDistance)
				{
					coords = std::pair<int, int>(zVIntercept, xVIntercept);
					visibleWalls[coords] = walls[coords];
				} else // Both are the same distance away (probably same coords), so add both to the list. 
				{
					std::pair<int, int> coords = std::pair<int, int>(zHIntercept, xHIntercept);
					visibleWalls[coords] = walls[coords];
					coords = std::pair<int, int>(zVIntercept, xVIntercept);
					visibleWalls[coords] = walls[coords];
				}
			
			}
			
		}	

	std::vector<TangentPolygonWorldObject *> visibleWallList;
	// Build list of the walls that are visible.
	for (std::map<std::pair<int, int>, TangentPolygonWorldObject*>::iterator it = visibleWalls.begin(); it != visibleWalls.end(); it++)
	{
		visibleWallList.push_back(it->second);
	}
	return visibleWallList;
}


bool Maze::collides(WorldObject* object)
{
	for (std::map<std::pair<int, int>, TangentPolygonWorldObject*>::iterator it = walls.begin(); it != walls.end(); it++)
	{
		WorldObject *wall = it->second;
		if (wall->collides(object))
			return true;
	}
	return false;
}