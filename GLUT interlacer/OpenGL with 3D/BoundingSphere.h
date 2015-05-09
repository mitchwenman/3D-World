#pragma once

#include "libs\glm\glm.hpp"
#include "GraphicsUtil.h"
#include "Transformation.h"
#include "WaveFrontPolygon.h"

class BoundingSphere
{

public:	
	double radius;

	glm::vec3 centrePoint;

	bool collides(BoundingSphere otherSphere);

	BoundingSphere() {};

	BoundingSphere(glm::vec3 center, double radius) : centrePoint(center), radius(radius) {};

	BoundingSphere(WaveFrontPolygon polygon);

};


class TransformableBoundingSphere : public BoundingSphere
{
private:
	glm::vec3 worldSpaceCentrePoint;

	double worldRadius;

	glm::mat4 worldMatrix;

public:
	TransformableBoundingSphere(WaveFrontPolygon polygon);

	TransformableBoundingSphere() {};

	void setTransform(std::vector<Transformation *> transforms);

	//! Produces a bounding sphere
	BoundingSphere* transform(); 
};