#pragma once

#include <string>
#include <vector>
#include "libs\glm\glm.hpp"
#include "GraphicsUtil.h"

class HeightMap
{
public:
	//! Generates a heightmap from an image.
	//! Also calculates normals and texture coordinates.
	//! @param path The path to the image used to generate the heightmap.
	void loadFromImage(std::string path);

	//!Renders the heightmap using a triangle strip and primitive restarts.
	void render();

	//! Gets the number of rows of the image.
	//! @return The number of rows of the input image.
	int getNumRows() { return rows; }

	//! Gets the number of columns of the image.
	//! @return The number of columns in the input image.
	int getNumColumns() { return columns; }

	//! Default constructor for the heightmap.
	HeightMap() {};

private:
	//! The number of rows and columns
	int rows, columns;

	//! The organised position data for the heightmap.
	std::vector<std::vector<Vertex3>> vertexData;

	//! The grouped normal data for the heightmap
	std::vector<std::vector<Vertex3>> normals;

	//! The grouped texture coordinate data for the heightmap
	std::vector<std::vector<Vertex2>> textureCoords;

	//! Indices for drawing of the heightmap. Needs to be drawn using
	//! GL_TRIANGLE_STRIP. Uses row * columns as the primitive restart index.
	//! GL_PRIMITIVE_RESTART must be enabled and set to rows * columns before calling GL_DRAW_ELEMENTS
	std::vector<unsigned int> indices;

	//! The ungrouped vertex data. Can be passed to glVertexPointer
	std::vector<double> vList;

	//! The ungrouped normal data. Can be passed to glNormalPointer
	std::vector<double> nList;

	//! The ungrouped texture coordinates. Can be passed to glTex_Coord_Pointer
	std::vector<double> tList;

	//! Calculates the normals for every vertex in the heightmap. Puts result in normals.
	void calculateNormals();

};