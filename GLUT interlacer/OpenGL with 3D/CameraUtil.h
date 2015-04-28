#pragma once

#include "GraphicsUtil.h"
#include "Camera.h"

namespace CameraUtil
{
	///Calculates the camera location by offsetting the eye by eyeDist
	///@param cam The left eye camera.
	///@param eyeDist The distance to the right of the current camera location.
	///@return The new eye vector after offset.
	Vertex3 calculateRightEye(Camera cam, double eyeDist);

	///Rotates the camera by a given angle.
	///@param cam The camera to be rotated.
	///@param diffAngle The angle to be rotated.
	void RotateCamera(Camera *cam, double diffAngle);

	///Applies the scalar to the camera eye and center vectors
	///@param cam The camera to be moved
	///@param scalar The amount of movement
	void MoveCamera(Camera *cam, double scalar);
}