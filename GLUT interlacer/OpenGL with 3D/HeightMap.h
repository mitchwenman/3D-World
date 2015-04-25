#pragma once

#include <string>
#include <vector>
#include "libs\glm\glm.hpp"
#include "GraphicsUtil.h"

class HeightMap
{
public:
	bool loadFromImage(std::string path);

	void render();

	int getNumRows();

	int getNumColumns();

	HeightMap() {};

private:
	int rows, columns;

	Vertex3 renderScale;

	std::vector<std::vector<Vertex3>> vertexData;

	std::vector<std::vector<Vertex3>> normals;

	std::vector<std::vector<Vertex2>> coordData;

};