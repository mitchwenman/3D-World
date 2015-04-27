#pragma once


#include <vector>

#include "WaveFrontPolygon.h"
#include "HeightMap.h"

class World
{
private:
	HeightMap *heightMap;

	World() {};

public:
	static World* getInstance();

	void draw();

	void setHeightMap(HeightMap *heightmap);

	
};