#include "WaveFrontPolygonDrawer.h"
#include "GraphicsSettings.h"
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
	std::vector<GLubyte> indices;
	for (unsigned int i = 0; i < polygon.faces.size(); i++)
	{
		indices.insert(indices.end(), polygon.faces[i].vertexIndices.begin(),
			polygon.faces[i].vertexIndices.end());
	}
	//XXX: random colours for now
	float colours[] = 
	{
		0, 1, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 1,
		1, 0, 1, 1, 0, 0
	};
	//GraphicsSettings::getSingleton()->setGLMatrices();
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_DOUBLE, 0, verts.data());
	glColorPointer(3, GL_FLOAT, 0, colours);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_BYTE, indices.data());
	glDisableClientState(GL_VERTEX_ARRAY);
}