#pragma once


#include <vector>

#include "WaveFrontPolygon.h"
#include "HeightMap.h"
#include "MaterialData.h"
#include "Transformation.h"

class World
{
private:
	HeightMap *heightMap;

	World() {};

public:
	std::vector<WaveFrontPolygon *> polygons;
	std::vector<MaterialData *> materials;
	std::vector<std::vector<Transformation*>> transformations;

	static World* getInstance();

	void draw();

	void setHeightMap(HeightMap *heightmap);

	void insertPolygon(WaveFrontPolygon *poly, MaterialData *mat, std::vector<Transformation*> trans = std::vector<Transformation*>());
	
};