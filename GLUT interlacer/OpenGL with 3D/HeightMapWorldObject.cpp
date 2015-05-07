#include "HeightMapWorldObject.h"
#include "GraphicsSettings.h"

#include "libs\glew.h"
#include "libs\glut.h"

void HeightMapWorldObject::draw()
{
	for (unsigned int i = 0; i < transformations.size(); i++)
	{
		transformations[i]->apply();
	}
	if (this->shaderProgram)
		shaderProgram->useProgram();
	else
		glUseProgram(0);
	GraphicsSettings::getSingleton()->setGLMatrices();
	this->heightmap->render();
}