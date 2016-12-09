#pragma once

#include "GraphicsUtil.h"
#include <string>
#include <vector>

class WaveFrontPolygon
{
public:

	//! The ungrouped position data.
	std::vector<float> vertices;

	//! The ungrouped texture coordinates.
	std::vector<float> textures;

	//! The ungrouped vertex normal data.
	std::vector<float> normals;

	//! The indices into vertices, passed to DrawElements
	std::vector<unsigned int> indices;

	//! Constructor for the object. Loads a polygon from file using tiny_obj_loader
	//! @param objFile The obj file that defines the polygon.
	WaveFrontPolygon(std::string objFile);

};


