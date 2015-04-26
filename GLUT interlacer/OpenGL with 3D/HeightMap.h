#pragma once

#include <string>
#include <vector>
#include "libs\glm\glm.hpp"
#include "GraphicsUtil.h"

class HeightMap
{
public:
	void loadFromImage(std::string path);

	void render();

	int getNumRows();

	int getNumColumns();

	HeightMap() {};

private:
	int rows, columns;

	std::vector<std::vector<Vertex3>> vertexData;

	std::vector<std::vector<Vertex3>> normals;

	std::vector<std::vector<Vertex2>> textureCoords;

	std::vector<unsigned int> indices;

	std::vector<double> vList;

	std::vector<double> nList;

	void calculateNormals();

};