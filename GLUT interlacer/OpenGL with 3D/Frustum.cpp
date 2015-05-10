#include "Frustum.h"
#include "GraphicsSettings.h"
#include "libs\glm\gtc\matrix_transform.hpp"

static Frustum* _instance;

Frustum::Frustum() : left(-.75), right(.75), top(1), bottom(-.5), nearPlane(1), farPlane(20)
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