///////////////////////////////////////////////////////////////////////////////////
// Filename: CameraUtil.cpp
// Author: Mitch Wenman
// Date Modified: 20/05/2015
// Description: Encapsulates the logic and properties of the directional light.
///////////////////////////////////////////////////////////////////////////////////

// ============== INCLUDES =================//
#include "DirectionalLight.h"
#include "Lighting.h"

// ============== GLOBALS =================//
static DirectionalLight* _instance;

// ============== FUNCTIONS =================//
DirectionalLight* DirectionalLight::getSingleton()
{
	if (!_instance)
	{
		_instance = new DirectionalLight();
	}
	return _instance;
}

void DirectionalLight::setLight()
{
	Lighting::setupDirectionalLight(direction, diffuse, ambient);
}

void DirectionalLight::setLight(Vertex4 direction, Vertex4 ambient, Vertex4 diffuse)
{
	this->direction = direction;
	this->ambient = ambient;
	this->diffuse = diffuse;
}