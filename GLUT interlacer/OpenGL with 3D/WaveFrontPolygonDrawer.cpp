#include "WaveFrontPolygonDrawer.h"
#include "GraphicsSettings.h"
#include "GraphicsUtil.h"
#include "libs\glew.h"
#include "libs\glut.h"


void WaveFrontPolygonDrawer::draw(WaveFrontPolygon polygon)
{
	//Create vertex array
	int numVerts = polygon.vertices.size();
	std::vector<double> verts;
	verts.reserve(numVerts * 3);
	for (int i = 0; i < numVerts; i++)
	{
		verts.push_back(polygon.vertices[i].x);
		verts.push_back(polygon.vertices[i].y);
		verts.push_back(polygon.vertices[i].z);
	}
	//Create array of indices into vertices
	std::vector<unsigned int> faceIndices;
	for (unsigned int i = 0; i < polygon.faces.size(); i++)
	{
		faceIndices.insert(faceIndices.end(), polygon.faces[i].vertexIndices.begin(),
			polygon.faces[i].vertexIndices.end());
	}
	//Multiple vertex normals - add together and then normalise
	std::vector<glm::vec3> normals(polygon.vertices.size());
	for (unsigned int i = 0; i < normals.size(); i++) normals[i] = glm::vec3(0, 0, 0); //Init with 0
	for (unsigned int i = 0; i < polygon.faces.size(); i++)
	{
		WaveFrontPolygonFace face = polygon.faces[i];
		for (unsigned int j = 0; j < face.normalIndices.size(); j++)
		{
			//Convert to vec, add to current normal
			glm::vec3 norm = GraphicsUtil::vertex3ToGLMVec3(polygon.normals[face.normalIndices[j]]);
			int vertn = face.vertexIndices[j];
			normals[vertn] += norm;
		}
	}
	//Loop through, normalise and create glnormal array
	std::vector<double> vertexNormals;
	for (unsigned int i = 0; i < normals.size(); i++)
	{
		glm::vec3 vertNormal = glm::normalize(normals[i]);
		vertexNormals.push_back(vertNormal.x);
		vertexNormals.push_back(vertNormal.y);
		vertexNormals.push_back(vertNormal.z);
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_DOUBLE, 0, verts.data());
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_DOUBLE, 0, vertexNormals.data());
	glDrawElements(GL_TRIANGLES, faceIndices.size(), GL_UNSIGNED_INT, faceIndices.data());
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}