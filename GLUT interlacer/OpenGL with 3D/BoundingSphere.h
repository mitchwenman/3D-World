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

	BoundingSphere(glm::vec3 center, double radius);

	BoundingSphere(WaveFrontPolygon polygon);

};


class TransformableBoundingSphere : public BoundingSphere
{
private:
	glm::vec3 worldSpaceCentrePoint;

	double worldRadius;

	glm::mat4 worldMatrix;

public:
	BoundingSphere transform(std::vector<Transformation *> transforms);

	BoundingSphere transform(); 
};