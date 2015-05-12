#pragma once

#include "GraphicsUtil.h"
#include "Camera.h"

namespace CameraUtil
{
	///Calculates the camera location for the right eye given the location for the left eye.
	///@param cam The left eye camera.
	///@param eyeDist The distance to the right of the current camera location.
	///@return The new eye vector after offset.
	Vertex3 calculateRightEye(Camera cam, double eyeDist);

	///Rotates the camera by a given angle.
	///@param cam The camera to be rotated.
	///@param diffAngle The angle to be rotated.
	void RotateCamera(Camera *cam, double diffAngle);

	///Applies the scalar to the camera eye and center vectors. This effectively moves the camera in the direction of the centre vector
	///but keeps a unit length distance between the eye and centre vectors.
	///@param cam The camera to be moved
	///@param scalar How far the camera should be moved. Use negative values for backwards movement.
	void MoveCamera(Camera *cam, double scalar);
};