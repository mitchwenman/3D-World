#include "Maze.h"
#include "SpecularNormalMap.h"
#include "Transformation.h"


Maze::Maze(std::string mazeFile, TangentWaveFrontPolygon* wall) : wall(wall)
{
	//Temporary maze for testing purposes
	bool tempMaze[5][5] = {
		{	true, true, true, true, true },
		{	true, false, false, false, true },
		{	true, false, false, false, true },
		{	true, false, false, false, true },
		{	true, true, true, true, true } };
	rows = columns = 5;
	this->maze.resize(5);
	for (int i = 0; i < rows; i++)
	{
		maze[i].resize(columns);
		for (int j = 0; j < columns; j++)
		{
			maze[i][j] = tempMaze[i][j];
		}
	}
	// Create objects from all walls
	IShaderProgram *program = new SpecularNormalMap("wood_floor.bmp", "wood_normal.bmp");
	//For each wall, create object with translations, add to wall map
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (maze[i][j]) //If there's a wall
			{
				//Create transformation
				Vertex4 trans = { j, 0, i, 0 };
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