#include "Camera.h"
#include "libs\glm\glm.hpp"
#include "libs\glm\gtc\matrix_transform.hpp"
#include "GraphicsUtil.h"
#include "GraphicsSettings.h"

static Camera* _instance;

Camera* Camera::getSingleton()
{
	if (!_instance)
	{
		_instance = new Camera();
	}
	return _instance;
}


void Camera::lookAt(double eyex, double eyey, double eyez, double centrex, double centrey, double centrez, double upx, double upy, double upz)
{
	Vertex3 eye = { eyex, eyey, eyez };
	Vertex3 center = { centrex, centrey, centrez };
	Vertex3 up = { upx, upy, upz };
	this->eye = eye;
	this->center = center;
	this->up = up;
	glm::vec3 eyeVec = glm::vec3(eye.x, eye.y, eye.z);
	glm::vec3 centerVec = glm::vec3(center.x, center.y, center.z);
	glm::vec3 upVec = glm::vec3(up.x, up.y, up.z);
	glm::mat4 lookAt = glm::lookAt(eyeVec, centerVec, upVec);
	GraphicsSettings::getSingleton()->modelViewMatrix *= lookAt;
}

glm::mat4 Camera::getLookAtMatrix()
{
	glm::vec3 eyeVec = glm::vec3(eye.x, eye.y, eye.z);
	glm::vec3 centerVec = glm::vec3(center.x, center.y, center.z);
	glm::vec3 upVec = glm::vec3(up.x, up.y, up.z);
	glm::mat4 lookAt = glm::lookAt(eyeVec, centerVec, upVec);
	return lookAt;
}

Camera::Camera()
{
	Vertex3 eye = { 0, 0, -1 };
	Vertex3 center = { 0, 0, 0 };
	Vertex3 up = { 0, 1, 0 };
	this->eye = eye;
	this->center = center;
	this->up = up;
}