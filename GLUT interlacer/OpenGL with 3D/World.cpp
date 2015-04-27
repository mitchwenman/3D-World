#include "World.h"

#include "WaveFrontPolygonDrawer.h"

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
	for (unsigned int i = 0; i < polygons.size(); i++)
	{
		materials[i]->setMaterial();
		WaveFrontPolygonDrawer::draw(*polygons[i]);
	}
}

void World::setHeightMap(HeightMap *heightmap)
{
	this->heightMap = heightmap;
}

void World::insertPolygon(WaveFrontPolygon *poly, MaterialData *mat, std::vector<Transformation*> trans)
{
	polygons.push_back(poly);
	materials.push_back(mat);
	transformations.push_back(trans);
}