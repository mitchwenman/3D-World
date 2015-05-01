#pragma once

#include "IShaderProgram.h"
#include "Texture.h"

#include <string>

class SpecularColourMap : public IShaderProgram
{
private:
	Texture texture;

public:
	SpecularColourMap(std::string textureFile);

	void useProgram();
};