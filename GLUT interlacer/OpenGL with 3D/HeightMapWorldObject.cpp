#include "HeightMapWorldObject.h"

void HeightMapWorldObject::draw()
{
	if (this->material)
		material->setMaterial();
	this->heightmap->render();
}