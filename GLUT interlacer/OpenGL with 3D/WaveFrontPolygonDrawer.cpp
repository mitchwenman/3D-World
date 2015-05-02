#include "WaveFrontPolygonDrawer.h"
#include "GraphicsSettings.h"
#include "GraphicsUtil.h"
#include "libs\glew.h"
#include "libs\glut.h"


void WaveFrontPolygonDrawer::draw(WaveFrontPolygon polygon)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	float* verts = polygon.vertices.data();
	glVertexPointer(3, GL_FLOAT, 0, verts);
	float* normals = polygon.normals.data();
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normals);
	unsigned int* indices = polygon.indices.data();
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, polygon.textures.data());
	glDrawElements(GL_TRIANGLES, polygon.indices.size(), GL_UNSIGNED_INT, indices);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void WaveFrontPolygonDrawer::drawNormalMapPolygon(TangentWaveFrontPolygon polygon)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	float* verts = polygon.vertices.data();
	glVertexPointer(3, GL_FLOAT, 0, verts);

	float* normals = polygon.normals.data();
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normals);

	float* tangents = polygon.tangents.data();
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, tangents);	
	
	unsigned int* indices = polygon.indices.data();
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, polygon.textures.data());

	glDrawElements(GL_TRIANGLES, polygon.indices.size(), GL_UNSIGNED_INT, indices);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}