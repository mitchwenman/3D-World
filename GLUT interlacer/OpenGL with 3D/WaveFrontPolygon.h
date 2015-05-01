#pragma once

#include "GraphicsUtil.h"
#include <string>
#include <vector>

class WaveFrontPolygon
{
public:
	std::vector<float> vertices;

	std::vector<float> textures;

	std::vector<float> normals;

	std::vector<unsigned int> indices;

	WaveFrontPolygon(std::string objFile);

};


