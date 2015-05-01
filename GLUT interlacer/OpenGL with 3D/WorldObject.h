#pragma once

#include "MaterialData.h"
#include "Transformation.h"
#include "IShaderProgram.h"
#include <vector>

class WorldObject
{
public:

	std::vector<Transformation*> transformations;

	IShaderProgram* shaderProgram;


	virtual void draw() = 0;

	WorldObject(IShaderProgram* shaderProgram = NULL, 
				std::vector<Transformation*> trans = std::vector<Transformation*>()) : shaderProgram(shaderProgram),
																						transformations(trans) {};
	

};