#pragma once

#include "MaterialData.h"
#include "Transformation.h"
#include <vector>

class WorldObject
{
public:
	MaterialData* material;

	std::vector<Transformation*> transformations;

	unsigned int shaderProgram;


	virtual void draw() = 0;

	WorldObject(MaterialData* material, 
				unsigned int shaderProgram = 0, 
				std::vector<Transformation*> trans = std::vector<Transformation*>()) : material(material), 
																						shaderProgram(shaderProgram),
																						transformations(trans) {};
	

};