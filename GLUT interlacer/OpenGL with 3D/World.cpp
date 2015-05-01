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
	for (unsigned int i = 0; i < objects.size(); i++)
	{		
		//gset->setGLMatrices();
		objects[i]->draw();
		gset->resetModelView();
		cam->setCamera();
	}
}

void World::insertObject(WorldObject* object)
{
	this->objects.push_back(object);
}