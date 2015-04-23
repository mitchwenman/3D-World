#include "CameraUtil.h"

Vertex3 CameraUtil::calculateRightEye(Camera cam, double eyeDist)
{
	Vertex3 rightEye = cam.eye;
	rightEye.x += eyeDist;//XXX: wrong testing
	return rightEye;
}