#include "DirectionalLight.h"
#include "Lighting.h"

static DirectionalLight* _instance;

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
	this->setLight();
}