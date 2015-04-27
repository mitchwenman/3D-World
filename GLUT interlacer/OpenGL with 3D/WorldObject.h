#pragma once

#include "MaterialData.h"
#include "Transformation.h"
#include <vector>

class WorldObject
{
private:
	MaterialData* material;

	std::vector<Transformation*> transformations;

	unsigned int shaderProgram;

public:
	virtual void draw() = 0;

	WorldObject(MaterialData* material, 
				unsigned int shaderProgram = 0, 
				std::vector<Transformation*> trans = std::vector<Transformation*>()) : material(material), 
																						shaderProgram(shaderProgram),
																						transformations(trans) {};
	

};