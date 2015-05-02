#include "TangentWaveFrontPolygon.h"
#include "libs\glm\glm.hpp"

TangentWaveFrontPolygon::TangentWaveFrontPolygon(std::string objFile) : WaveFrontPolygon(objFile)
{
	//Group vertices and texture coords so it's easier to calculate
	std::vector<glm::vec3> verts;
	std::vector<glm::vec2> tCoords;

	for (unsigned int i = 0; i < this->vertices.size(); i += 3)
	{
		double x = vertices[i];
		double y = vertices[i + 1];
		double z = vertices[i + 2];
		verts.push_back(glm::vec3(x, y, z));
	}

	for (unsigned int i = 0; i < this->textures.size(); i += 2)
	{
		double u = textures[i];
		double v = textures[i + 1];
		tCoords.push_back(glm::vec2(u, v));
	}
}