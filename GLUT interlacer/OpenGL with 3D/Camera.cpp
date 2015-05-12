#include "Camera.h"
#include "libs\glm\glm.hpp"
#include "libs\glm\gtc\matrix_transform.hpp"
#include "GraphicsUtil.h"
#include "GraphicsSettings.h"
#include <math.h>
#include "libs\glew.h"
#include "libs\glut.h"

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
	this->boundingSphere.centrePoint = GraphicsUtil::vertex3ToGLMVec3(eye);
	boundingSphere.radius = .25;
}

void Camera::setCamera()
{
	GraphicsSettings::getSingleton()->modelViewMatrix *= this->getLookAtMatrix();
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
	this->boundingSphere = *(new TransformableBoundingSphere());
	this->lookAt(5.5, .5, 9, 5.5, .5, 8, 0, 1, 0);
	angle = 0.0;
	
	
}

void Camera::setAngle(double angle)
{
	this->angle = fmod(angle + 2 * (atan(1.0) * 4), 2 * (atan(1.0) * 4));
}

bool Camera::collides(WorldObject *otherObject)
{
	//Create transformation for bounding sphere
	std::vector<Transformation*> transforms;
		
	boundingSphere.centrePoint = GraphicsUtil::vertex3ToGLMVec3(eye);
	otherObject->boundingSphere.setTransform(otherObject->transformations);
	BoundingSphere *otherSphere = otherObject->boundingSphere.transform();

	bool collides = boundingSphere.collides(*otherSphere);
	delete(otherSphere);
	return collides;
}