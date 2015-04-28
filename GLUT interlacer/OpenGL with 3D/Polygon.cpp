#include "Polygon.h"
#include "WaveFrontPolygon.h"
#include "WaveFrontPolygonDrawer.h"
#include "GraphicsSettings.h"
#include "libs\glew.h"
#include "libs\glut.h"

void PolygonWorldObject::draw()
{
	for (unsigned int i = 0; i < this->transformations.size(); i++)
	{
		transformations[i]->apply();
	}
	if (this->material)
		material->setMaterial();
	GraphicsSettings::getSingleton()->setGLMatrices();
	glUseProgram(this->shaderProgram);
	WaveFrontPolygonDrawer::draw(*this->polygon);
}