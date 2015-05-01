#pragma once

#include "GraphicsUtil.h"

class DirectionalLight
{
private:
	DirectionalLight() {};

	Vertex4 direction;
	Vertex4 ambient,
			diffuse;

public:
	DirectionalLight* getSingleton();

	void setLight();
	
	void setLight(Vertex4 direction, Vertex4 ambient, Vertex4 diffuse);

	Vertex4 getDirection() { return direction; }
};