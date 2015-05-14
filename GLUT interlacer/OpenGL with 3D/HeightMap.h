#pragma once

#include <string>
#include <vector>
#include "libs\glm\glm.hpp"
#include "GraphicsUtil.h"

//! A class for representing terrain generated from a height map.
/*!
	This class loads and creates a mesh representation of a heightmap, which can later be used
	for rendering terrain. The heightmap is loaded such that it can be drawn using triangle strips
	and openGl's primitive restart function. The vertex normals of the heightmap are also calculated.
*/
class HeightMap
{
public:
	//! Generates a heightmap from an image.
	//! Also calculates normals and texture coordinates.
	/*!
		Pseudocode:
		@verbatim
			for (i < image.rows)
				for (j < image.columns)
					Vertices.add(i * scale, image[i][j] / 64, j * scale)
					Texture.add(i * texScaleX, j * texScaleZ)
			calculateNormals()
			//Build triangle strip
			for (i < rows - 1)
				for (j < rows - 1)
					indices.add(i * columns + j)
					indices.add((i + 1) * columns + j)
			indices.add(row * columns) //Add primitive restart index
		@endverbatim
	*/
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
	/*! 
		Pseudocode:
		@verbatim
			for (each quad)
				calculateNormal(leftTriangle)
				calculateNormal(rightTriangle)
			for (i < rows)
				for (j < columns)
					normal = vec3(0)
					if (!topRow && !leftColumn)
						normal += topLeftQuad.RightTriangle.Normal
					if (!topRow && !rightColumn)
						normal += topRightQuad.LeftTriangle.Normal
						normal += topRightQuad.RightTriangle.Normal
					if (!bottomRow && !leftColumn)
						normal += bottomLeftQuad.LeftTriangle.Normal
						normal += bottomRightQuad.RightTriangle.Normal
					if (!bottomRow && !rightColumn)
						normal += bottomRightQuad.LeftTriangle.Normal
					finalNormal = normalise(normal)
					normals[i][j] = finalNormal					
		@endverbatim
	*/
	void calculateNormals();

};