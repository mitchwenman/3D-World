#pragma once

#include "libs\glm\glm.hpp"

class Frustum
{
private:

	Frustum(); 

public:
	double		left, right, top, bottom,
				nearPlane, farPlane;

	glm::mat4 frustumMatrix;

	static Frustum* getSingleton();

	void setFrustum();

	void setFrustum(double left, double right, double top, double bottom, double near, double far);



};