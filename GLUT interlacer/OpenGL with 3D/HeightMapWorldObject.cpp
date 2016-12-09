///////////////////////////////////////////////////////////////////////////////////
// Filename: HeightmapWorldObject.cpp
// Author: Mitch Wenman
// Date Modified: 20/05/2015
// Description: Encapsulates a height map and related shader program.
///////////////////////////////////////////////////////////////////////////////////

// ============== INCLUDES =================//
#include "HeightMapWorldObject.h"
#include "GraphicsSettings.h"

#include "libs\glew.h"
#include "libs\glut.h"

// ============== FUNCTIONS =================//
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