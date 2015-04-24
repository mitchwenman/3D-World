#pragma once

#include "libs\glew.h"
#include "libs\glut.h"

#include "GraphicsUtil.h"

namespace Lighting
{
	void setupDirectionalLight(Vertex4 direction, Vertex4 diffuse, Vertex4 ambient);

	void setupPointLight(Vertex4 position, Vertex4 diffuse, Vertex4 ambient); 

	void setupSpotLight(Vertex4 position, Vertex4 diffuse, Vertex4 ambient, Vertex3 direction, float cutoff);
};

