#include "CameraUtil.h"
#include "libs\glm\glm.hpp"
#include "libs\glm\gtc\matrix_transform.hpp"

Vertex3 CameraUtil::calculateRightEye(Camera cam, double eyeDist)
{
	Vertex3 eye = cam.getEye();
	Vertex3 center = cam.getCentre();
	glm::vec3 leftEye = glm::vec3(eye.x, eye.y, eye.z); //Left eye vector
	glm::vec3 at = glm::vec3(center.x, center.y, center.z); //AT vector
	glm::vec3 U = glm::vec3(0, 1, 0); 
	glm::vec3 F = at - leftEye;
	glm::vec3 V = glm::cross(glm::normalize(F), glm::normalize(U));
	glm::vec3 R = leftEye + (V * (float)eyeDist); //Convert to float for template

	Vertex3 rightEye = { R.x, R.y, R.z }; //Put result into return vertex3
	rightEye.x += eyeDist;
	return rightEye;
}