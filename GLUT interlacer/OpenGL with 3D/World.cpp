#include "World.h"

#include "WaveFrontPolygonDrawer.h"
#include "Camera.h"
#include "GraphicsSettings.h"
#include "HighlightShaderProgram.h"

static World* _instance;

World* World::getInstance()
{
	if (!_instance)
		_instance = new World();
	return _instance;
}

World::World() : currentSelectedPolygonShader(NULL), selectedObject(-1)
{
	this->hightlightShader = new HighlightShaderProgram();
}


void World::draw()
{
	GraphicsSettings *gset = GraphicsSettings::getSingleton();
	Camera* cam = Camera::getSingleton();
	gset->resetModelView();
	cam->setCamera();
	if (this->heightMap)
	{
		heightMap->draw();
		gset->resetModelView();
		cam->setCamera();
	}
	if (maze != NULL)
	{
		maze->render(cam->getEye(), cam->getAngle(), 85);
		gset->resetModelView();
		cam->setCamera();
	}
	std::vector<WorldObject *> allObjects;
	allObjects.insert(allObjects.begin(), objects.begin(), objects.end());
	allObjects.insert(allObjects.end(), staticObjects.begin(), staticObjects.end());
	for (unsigned int i = 0; i < allObjects.size(); i++)
	{		
		gset->setGLMatrices();
		allObjects[i]->draw();
		gset->resetModelView();
		cam->setCamera();
	}
}

void World::insertObject(WorldObject* object)
{
	this->objects.push_back(object);
}

void World::toggleSelectedObject()
{
	if (selectedObject != -1)
	{
		//Swap back shader program to object
		objects[selectedObject]->shaderProgram = currentSelectedPolygonShader;
	}
	//Increment selected poly
	selectedObject++;
	if (selectedObject == objects.size()) 
	{
		selectedObject = -1;
		return;
	}
	//Swap out shader program
	currentSelectedPolygonShader = objects[selectedObject]->shaderProgram;
	objects[selectedObject]->shaderProgram = hightlightShader;
}

std::vector<WorldObject *> World::getAllObjects()
{
	std::vector<WorldObject *> allObjects;
	allObjects.insert(allObjects.begin(), objects.begin(), objects.end());
	allObjects.insert(allObjects.end(), staticObjects.begin(), staticObjects.end());
	return allObjects;
}