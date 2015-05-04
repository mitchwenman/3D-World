#include "Maze.h"
#include "SpecularNormalMap.h"
#include "Transformation.h"
#include "GraphicsSettings.h"
#include "Camera.h"
#include "MazeReader.h"


Maze::Maze(std::string mazeFile, TangentWaveFrontPolygon* wall) : wall(wall), xOffset(-3.5), zOffset(-2.5)
{
	std::vector<std::vector<bool>> wallData = MazeReader::readFromFile(mazeFile);
	//Temporary maze for testing purposes
	bool tempMaze[10][10] = {
		{	true, true, true, true, true, true, true, true, true, true },
		{	true, false, false, false, false, false, false, false, false, true },
		{	true, false, false, false, false, false, false, false, false, true },
		{	true, false, false, false, false, false, false, false, false, true },
		{	true, false, false, false, false, false, false, false, false, true },
		{	true, false, false, false, false, false, false, false, false, true }, 
		{	true, false, false, false, false, false, false, false, false, true }, 
		{	true, false, false, false, false, false, false, false, false, true }, 
		{	true, false, false, false, false, false, false, false, false, true }, 
		{	true, true, true, true, true, true, true, true, true, true }
	};
	rows = columns = 10;
	this->maze.resize(rows);
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
	//Check if player inside maze, else render everything

	GraphicsSettings *gset = GraphicsSettings::getSingleton();
	gset->resetModelView();
	Camera::getSingleton()->setCamera();
	for (std::map<std::pair<int, int>, TangentPolygonWorldObject*>::iterator it = walls.begin(); it != walls.end(); it++)
	{
		TangentPolygonWorldObject *wallObject = it->second;
		wallObject->draw();
		gset->resetModelView();
		Camera::getSingleton()->setCamera();

	}
}