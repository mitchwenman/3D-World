#include "HeightMapWorldObject.h"

#include "libs\glew.h"
#include "libs\glut.h"

void HeightMapWorldObject::draw()
{
	if (this->shaderProgram)
		shaderProgram->useProgram();
	else
		glUseProgram(0);
	this->heightmap->render();
}