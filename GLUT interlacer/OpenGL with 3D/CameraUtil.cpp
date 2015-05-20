///////////////////////////////////////////////////////////////////////////////////
// Filename: CameraUtil.cpp
// Author: Mitch Wenman
// Date Modified: 20/05/2015
// Description: Groups together useful functions for manipulating the camera.
///////////////////////////////////////////////////////////////////////////////////

// ============== INCLUDES =================//
#include "CameraUtil.h"
#include "libs\glm\glm.hpp"
#include "libs\glm\gtc\matrix_transform.hpp"
#include "CollisionDetection.h"

// ============== FUNCTIONS =================//
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

void CameraUtil::RotateCamera(Camera *cam, double diffAngle)
{	
	//Get current angle
	double angle = cam->getAngle();
	//Decrease angle
	double newAngle = angle + diffAngle;
	//Calculate new line of sight
	double lx = sin(newAngle);
	double lz = -cos(newAngle);
	//Add values to lookAt
	Vertex3 eye = cam->getEye();
	Vertex3 centre = cam->getCentre();
	Vertex3 up = cam->getUp();
	centre.x = eye.x + lx;
	centre.z = eye.z + lz;
	cam->lookAt(eye.x, eye.y, eye.z, centre.x, centre.y, centre.z, up.x, up.y, up.z);
	cam->setAngle(newAngle);

}

void CameraUtil::MoveCamera(Camera *cam, double scalar)
{
	if (scalar != 0)
	{
		Camera* cam = Camera::getSingleton();
		//Get line of sight 
		double angle = cam->getAngle();
		double lx = sin(angle);
		double lz = -cos(angle);
		//Move both eye and lookAt along same path
		Vertex3 eye, oldEye;
		eye = oldEye = cam->getEye();

		Vertex3 centre, oldCentre;
		centre = oldCentre = cam->getCentre();

		Vertex3 up = cam->getUp();

		eye.x += lx * scalar;
		eye.z += lz * scalar;			
		centre.x += lx * scalar;
		centre.z += lz * scalar;
		cam->lookAt(eye.x, eye.y, eye.z, centre.x, centre.y, centre.z, up.x, up.y, up.z);
		if (CollisionDetection::cameraCollidesWithWorld())
		{
			cam->lookAt(oldEye.x, oldEye.y, oldEye.z, oldCentre.x, oldCentre.y, oldCentre.z, up.x, up.y, up.z);
		}

	}
	
}