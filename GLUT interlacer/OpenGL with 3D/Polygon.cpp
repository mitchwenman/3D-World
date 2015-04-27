#include "Polygon.h"
#include "WaveFrontPolygon.h"
#include "WaveFrontPolygonDrawer.h"
#include "GraphicsSettings.h"

void PolygonWorldObject::draw()
{
	for (unsigned int i = 0; i < this->transformations.size(); i++)
	{
		transformations[i]->apply();
	}
	if (this->material)
		material->setMaterial();
	GraphicsSettings::getSingleton()->setGLMatrices();
	WaveFrontPolygonDrawer::draw(*this->polygon);
}