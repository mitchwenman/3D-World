#pragma once

#include "libs\glm\glm.hpp"
#include "GraphicsUtil.h"
#include "Transformation.h"
#include "WaveFrontPolygon.h"

class BoundingSphere
{

public:	
	double radius;

	glm::vec4 centrePoint;

	bool collides(BoundingSphere otherSphere);

	BoundingSphere(glm::vec3 center, double radius);

	BoundingSphere(WaveFrontPolygon polygon);

};