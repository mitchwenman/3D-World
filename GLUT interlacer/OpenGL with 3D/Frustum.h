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

	///Returns the frustum singleton instance
	///@return the frustum singleton instance
	static Frustum* getSingleton();

	///Multiplies the projection matrix by the frustum matrix
	void setFrustum();

	///Creates a frustum matrix from the given values
	///@param left, right The x values of the left, right edges
	///@param top, bottom The y values of the bottom, top edges
	///@param near, far The z values of the near and far plane.
	void setFrustum(double left, double right, double top, double bottom, double near, double far);



};