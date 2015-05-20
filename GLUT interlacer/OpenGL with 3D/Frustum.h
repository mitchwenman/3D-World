#pragma once

#include "libs\glm\glm.hpp"

//! An OOP wrapper for setting up a Frustum projection. 
/*!
	This class implements the singleton pattern. Calls to setFrustum()
	modify the projection matrix held by the GraphicsSettings singleton object,
	which is eventually given to openGL.
*/
class Frustum
{
private:
	//! Creates and intialises the frustum matrix with the following values: left(-.75), right(.75), top(1), bottom(-.5), nearPlane(1), farPlane(20).
	//! Does not actually set the projection matrix until Frustum() is called.
	Frustum(); 

public:
	double		left, right, top, bottom,
				nearPlane, farPlane;

	//! The matrix representing the frustum transformation.
	glm::mat4 frustumMatrix;

	//! Returns the frustum singleton instance
	//! @return The frustum singleton instance
	static Frustum* getSingleton();

	//! Multiplies the projection matrix by the frustum matrix
	//! @sideeffect All objects drawn after this call will use the frustum matrix defined in this object until the projection matrix is reset.
	void setFrustum();

	//! Modifies the frustum matrix held by this object to reflect the given values. Does not set the projection
	//! matrix until setFrustum() is called.
	//! @param left, right The x values of the left, right edges
	//! @param top, bottom The y values of the bottom, top edges
	//! @param near, far The z values of the near and far plane.
	void setFrustum(double left, double right, double top, double bottom, double near, double far);



};