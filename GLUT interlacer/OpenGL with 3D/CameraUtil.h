#pragma once

#include "GraphicsUtil.h"
#include "Camera.h"

namespace CameraUtil
{
	Vertex3 calculateRightEye(Camera camera, double eyeDist);
};