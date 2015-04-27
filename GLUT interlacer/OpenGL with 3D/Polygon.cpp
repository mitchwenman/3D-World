#include "Polygon.h"
#include "WaveFrontPolygon.h"
#include "WaveFrontPolygonDrawer.h"

void Polygon::draw()
{
	for (unsigned int i = 0; i < this->transformations.size(); i++)
	{
		transformations[i]->apply();
	}
	WaveFrontPolygonDrawer::draw(*this->polygon);
}