#pragma once

#include "IShaderProgram.h"
#include "Texture.h"

#include <string>

class SpecularNormalMap : public IShaderProgram
{
private:
	Texture* texture;

	Texture* normalMap;

public:
	SpecularNormalMap(std::string texture, std::string normalMap);

	void useProgram();

};