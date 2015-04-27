#pragma once


#include <vector>

#include "WaveFrontPolygon.h"
#include "HeightMap.h"
#include "MaterialData.h"
#include "Transformation.h"
#include "WorldObject.h"

class World
{
private:
	HeightMap *heightMap;

	World() {};

public:
	std::vector<WorldObject *> objects;

	static World* getInstance();

	void draw();

	void insertObject(WorldObject *object);
	
};