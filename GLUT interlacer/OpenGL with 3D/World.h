#pragma once


#include <vector>

#include "WaveFrontPolygon.h"
#include "HeightMap.h"
#include "MaterialData.h"
#include "Transformation.h"
#include "WorldObject.h"
#include "IShaderProgram.h"

class World
{
private:
	int selectedObject;

	IShaderProgram* hightlightShader;

	IShaderProgram* currentSelectedPolygonShader;

	World();




public:
	std::vector<WorldObject *> objects;

	static World* getInstance();

	void draw();

	void insertObject(WorldObject *object);
	
	void toggleSelectedObject();

	int getSelectedObject() { return selectedObject; }
};