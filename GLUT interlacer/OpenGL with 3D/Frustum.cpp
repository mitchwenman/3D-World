///////////////////////////////////////////////////////////////////////////////////
// Filename: CameraUtil.cpp
// Author: Mitch Wenman
// Date Modified: 20/05/2015
// Description: Defines the logic and properties of the viewing frustum.
///////////////////////////////////////////////////////////////////////////////////

// ============== INCLUDES =================//
#include "Frustum.h"
#include "GraphicsSettings.h"
#include "libs\glm\gtc\matrix_transform.hpp"

// ============== GLOBALS =================//
static Frustum* _instance;

// ============== FUNCTIONS =================//
Frustum::Frustum() : left(-.75), right(.75), top(1), bottom(-.5), nearPlane(1), farPlane(25)
{
	frustumMatrix = glm::frustum(left, right, bottom, top, nearPlane, farPlane);
}

Frustum* Frustum::getSingleton()
{
	if (!_instance)
	{
		_instance = new Frustum();
	}
	return _instance;
}

void Frustum::setFrustum()
{
	GraphicsSettings::getSingleton()->projectionViewMatrix *= this->frustumMatrix;
}

void Frustum::setFrustum(double left, double right, double top, double bottom, double near, double far) 
{
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
	this->farPlane = far;
	this->nearPlane = near;
	this->setFrustum();
}