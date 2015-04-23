#include "Camera.h"
#include "libs\glm\glm.hpp"
#include "libs\glm\gtc\matrix_transform.hpp"
#include "GraphicsUtil.h"
#include "GraphicsSettings.h"
#include <math.h>

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
	//angle = asin(centrex - eyex);
}

void Camera::moveEye(double eyex, double eyey, double eyez)
{
	eyex += eye.x;
	eyey += eye.y;
	eyez += eye.z;
	angle = asin(this->center.x - this->eye.x);
	this->lookAt(eyex, eyey, eyez, center.x, center.y, center.z, up.x, up.y, up.z);
}

void Camera::setCamera()
{
	glm::mat4 lookAt = this->getLookAtMatrix();
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
	this->lookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);
	angle = 0;
}