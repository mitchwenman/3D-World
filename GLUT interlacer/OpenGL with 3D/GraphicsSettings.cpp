#include "GraphicsSettings.h"
#include "libs\glew.h"
#include "libs\glut.h"
#include "libs\glm\gtc\matrix_transform.hpp"
#include "libs\glm\gtc\type_ptr.hpp"

static GraphicsSettings* _instance;

#include <iostream>
#include "libs\glm\ext.hpp"
#include "Camera.h"

GraphicsSettings::GraphicsSettings() {};

GraphicsSettings* GraphicsSettings::getSingleton()
{
	if ( !_instance )
	{
		_instance = new GraphicsSettings();
	}
	return _instance;
}

void GraphicsSettings::setGLMatrices()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(modelViewMatrix));
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(projectionViewMatrix));
}
