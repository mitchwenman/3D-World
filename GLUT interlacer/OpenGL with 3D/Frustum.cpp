#include "Frustum.h"
#include "GraphicsSettings.h"
#include "libs\glm\gtc\matrix_transform.hpp"

static Frustum* _instance;

Frustum::Frustum() : left(-1), right(1), top(1), bottom(-1), nearPlane(1), farPlane(50)
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
	GraphicsSettings* gset = GraphicsSettings::getSingleton();
	gset->projectionViewMatrix *= frustumMatrix;
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