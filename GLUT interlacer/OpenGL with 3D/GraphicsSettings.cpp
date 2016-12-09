///////////////////////////////////////////////////////////////////////////////////
// Filename: GraphicsSettings.cpp
// Author: Mitch Wenman
// Date Modified: 20/05/2015
// Description: Defines the model and projection matrices and other various properties.
///////////////////////////////////////////////////////////////////////////////////

// ============== INCLUDES =================//
#include "GraphicsSettings.h"
#include "libs\glew.h"
#include "libs\glut.h"
#include "libs\glm\gtc\matrix_transform.hpp"
#include "libs\glm\gtc\type_ptr.hpp"
#include <iostream>
#include "libs\glm\ext.hpp"
#include "Camera.h"

// ============== GLOBALS =================//
static GraphicsSettings* _instance;


// ============== FUNCTIONS =================//
GraphicsSettings::GraphicsSettings() : drawBoundingSphere(false) {};

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


void GraphicsSettings::resetModelView()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	modelViewMatrix = glm::mat4();
}

void GraphicsSettings::resetProjectionView()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	projectionViewMatrix = glm::mat4();
}