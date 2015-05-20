///////////////////////////////////////////////////////////////////////////////////
// Filename: WaveFrontPolygon.cpp
// Author: Mitch Wenman
// Date Modified: 20/05/2015
// Description: Stores an obj file's data so it can be drawn.
///////////////////////////////////////////////////////////////////////////////////


// ============== INCLUDES =================//
#include "WaveFrontPolygon.h"
#include "tiny_obj_loader.h"

// ============== FUNCTIONS =================//
WaveFrontPolygon::WaveFrontPolygon(std::string objFile)
{
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> mats;
	tinyobj::LoadObj(shapes, mats, objFile.c_str());
	this->vertices = shapes[0].mesh.positions;
	this->normals = shapes[0].mesh.normals;
	this->textures = shapes[0].mesh.texcoords;
	this->indices = shapes[0].mesh.indices;
}