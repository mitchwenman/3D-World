#pragma once

#include "GraphicsUtil.h"
#include <vector>

class WaveFrontPolygonFace
{
public:
	std::vector<int> vertexIndices;

	std::vector<int> textureIndices;

	std::vector<int> normalIndices;

};

class WaveFrontPolygon
{
public:
	std::vector<Vertex4> vertices;

	std::vector<Vertex2> textures;

	std::vector<Vertex3> normals;

	std::vector<WaveFrontPolygonFace> faces;
};


