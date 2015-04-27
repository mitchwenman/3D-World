#include "World.h"

static World* _instance;

World* World::getInstance()
{
	if (!_instance)
		_instance = new World();
	return _instance;
}

void World::draw()
{
	this->heightMap->render();
}

void World::setHeightMap(HeightMap *heightmap)
{
	this->heightMap = heightmap;
}