#include "World.h"

#include "WaveFrontPolygonDrawer.h"
#include "Camera.h"
#include "GraphicsSettings.h"

static World* _instance;

World* World::getInstance()
{
	if (!_instance)
		_instance = new World();
	return _instance;
}

void World::draw()
{
	GraphicsSettings *gset = GraphicsSettings::getSingleton();
	Camera* cam = Camera::getSingleton();
	gset->resetModelView();
	cam->setCamera();
	gset->setGLMatrices();
	this->heightMap->render();
	for (unsigned int i = 0; i < polygons.size(); i++)
	{		
		for (unsigned int j = 0; j < transformations[i].size(); j++)
		{
			Transformation *t = transformations[i][j];
			if (t != NULL)
			{
				t->apply();
			}
		}
		gset->setGLMatrices();
		materials[i]->setMaterial();
		WaveFrontPolygonDrawer::draw(*polygons[i]);
		gset->resetModelView();
		cam->setCamera();
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