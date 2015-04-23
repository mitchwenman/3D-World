#pragma once

#include "GraphicsUtil.h"
#include "Camera.h"

namespace CameraUtil
{
	Vertex3 calculateRightEye(Camera cam, double eyeDist);

	void RotateCamera(Camera *cam, double diffAngle);

	void MoveCamera(Camera *cam, double scalar);
}