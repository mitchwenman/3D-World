#include "HeightMapWorldObject.h"

#include "libs\glew.h"
#include "libs\glut.h"

void HeightMapWorldObject::draw()
{
	glUseProgram(this->shaderProgram);
	if (this->material)
		material->setMaterial();
	this->heightmap->render();
}