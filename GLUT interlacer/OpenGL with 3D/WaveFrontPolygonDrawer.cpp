#include "WaveFrontPolygonDrawer.h"
#include "GraphicsSettings.h"
#include "libs\glew.h"
#include "libs\glut.h"


void WaveFrontPolygonDrawer::draw(WaveFrontPolygon polygon)
{
	//Create vertex array
	int numVerts = polygon.vertices.size();
	std::vector<double> verts;
	std::vector<double> normals;
	verts.reserve(numVerts * 3);
	for (int i = 0; i < numVerts; i++)
	{
		verts.push_back(polygon.vertices[i].x);
		verts.push_back(polygon.vertices[i].y);
		verts.push_back(polygon.vertices[i].z);
	}
	//Create array of indices into vertices
	std::vector<GLubyte> faceIndices;
	for (unsigned int i = 0; i < polygon.faces.size(); i++)
	{
		faceIndices.insert(faceIndices.end(), polygon.faces[i].vertexIndices.begin(),
			polygon.faces[i].vertexIndices.end());
	}

	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_DOUBLE, 0, verts.data());

	glDrawElements(GL_TRIANGLES, faceIndices.size(), GL_UNSIGNED_BYTE, faceIndices.data());
	glDisableClientState(GL_VERTEX_ARRAY);
}