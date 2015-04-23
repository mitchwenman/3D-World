#include "CameraUtil.h"
#include "libs\glm\glm.hpp"
#include "libs\glm\gtc\matrix_transform.hpp"

Vertex3 CameraUtil::calculateRightEye(Camera cam, double eyeDist)
{
	glm::vec3 leftEye = glm::vec3(cam.eye.x, cam.eye.y, cam.eye.z); //Left eye vector
	glm::vec3 at = glm::vec3(cam.center.x, cam.center.y, cam.center.z); //AT vector
	glm::vec3 U = glm::vec3(0, 1, 0); 
	glm::vec3 F = at - leftEye;
	glm::vec3 V = glm::cross(glm::normalize(F), glm::normalize(U));
	glm::vec3 R = leftEye + (V * (float)eyeDist); //Convert to float for template

	Vertex3 rightEye = { R.x, R.y, R.z }; //Put result into return vertex3
	rightEye.x += eyeDist;
	return rightEye;
}