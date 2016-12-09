#pragma once

#include "libs\glew.h"
#include "libs\glut.h"

#include "GraphicsUtil.h"

//! A namespace for grouping together functions for setting up directional, point and spotlights.
namespace Lighting
{
	//! Encapsulates the opengGL lightfv calls required to set up a directional light with the given values.
	//! @param direction The direction vector of the light. The w component should be 0.
	//! @param diffuse The diffuse colour of the light.
	//! @param ambient The ambient colour of the light.
	void setupDirectionalLight(Vertex4 direction, Vertex4 diffuse, Vertex4 ambient);

	//! Encapsulates the opengGL lightfv calls required to set up a point light with the given values.
	//! @param position The position of the light. The w component should be 1.
	//! @param diffuse The diffuse colour of the light.
	//! @param ambient The ambient colour of the light.
	void setupPointLight(Vertex4 position, Vertex4 diffuse, Vertex4 ambient); 

	//! Encapsulates the opengGL lightfv calls required to set up a spotlight with the given values.
	//! @param position The position of the light. The w component should be 1.
	//! @param diffuse The diffuse colour of the light.
	//! @param ambient The ambient colour of the light.
	//! @param direction The direction of the light.
	//! @param cutoff The spotlight cutoff angle. E.g. the diameter of the beam.
	void setupSpotLight(Vertex4 position, Vertex4 diffuse, Vertex4 ambient, Vertex3 direction, float cutoff);
};

