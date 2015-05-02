#include "TangentWaveFrontPolygon.h"
#include "libs\glm\glm.hpp"
#include "libs\glm\gtx\transform.hpp"

///Loosely based on this tutorial: http://ogldev.atspace.co.uk/www/tutorial26/tutorial26.html
///and Mathematics for Games Programming

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
	std::vector<glm::vec3> tangentVectors(verts.size());
	//Calculate tangent vector for all triangles, normalise result for each vector
	for (unsigned int i = 0; i < this->indices.size(); i += 3)
	{
		//Get triangle verts
		glm::vec3 v0 = verts[indices[i]];
		glm::vec3 v1 = verts[indices[i + 1]];
		glm::vec3 v2 = verts[indices[i + 2]];

		//Create edges
		glm::vec3 edge1 = v1 - v0;
		glm::vec3 edge2 = v2 - v0;

		//Get uv coords
		glm::vec2 uv0 = tCoords[indices[i]];
		glm::vec2 uv1 = tCoords[indices[i + 1]];
		glm::vec2 uv2 = tCoords[indices[i + 2]];

		//Create uv and edge matrices
		glm::vec2 deltaUV1 = uv1 - uv0;
		glm::vec2 deltaUV2 = uv2 - uv0;
		glm::mat2 uvMatrix = glm::mat2(deltaUV1.x, deltaUV2.x, deltaUV1.y, deltaUV2.y);
		glm::mat2 inverseUVMatrix = glm::inverse(uvMatrix);

		glm::mat3x2 edgeMatrix = glm::mat3x2(edge1.x, edge2.x, edge1.y, edge2.y, edge1.z, edge2.z);

		//Calculate TB matrix
		glm::mat3x2 tb = inverseUVMatrix * edgeMatrix;
		glm::vec3 tangent = glm::vec3(tb[0].x, tb[1].x, tb[2].x);

		//Vertex tangent = normalise(sum of all adjacent surface tangents)
		tangentVectors[indices[i]] += tangent;
		tangentVectors[indices[i + 1]] += tangent;
		tangentVectors[indices[i + 2]] += tangent;

	}
	//Normalise and add to data
	for (unsigned int i = 0; i < tangentVectors.size(); i++)
	{
		glm::vec3 normTangent = glm::normalize(tangentVectors[i]);
		tangents.push_back(normTangent.x);
		tangents.push_back(normTangent.y);
		tangents.push_back(normTangent.z);
	}
	
}