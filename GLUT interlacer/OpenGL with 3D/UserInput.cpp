#include "UserInput.h"
#include "libs\glew.h"
#include "libs\glut.h"
#include "Camera.h"
#include <math.h>

void UserInput::handleKeyInput(unsigned char c, int x, int y)
{
	switch (c)
	{
	case GLUT_KEY_LEFT:
		{
			Camera* cam = Camera::getSingleton();
			//Get current angle
			double angle = cam->getAngle();
			//Decrease angle
			double newAngle = angle - 0.1;
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
			break;
		}
	case GLUT_KEY_RIGHT:
		{
			Camera* cam = Camera::getSingleton();
			//Get current angle
			double angle = cam->getAngle();
			//Increase angle
			double newAngle = angle + 0.1;
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
			break;
		}

	case GLUT_KEY_UP:
		{
			Camera* cam = Camera::getSingleton();
			//Get line of sight 
			double angle = cam->getAngle();
			double lx = sin(angle);
			double lz = -cos(angle);
			//Move both eye and lookAt along same path
			double scalar = 0.1;
			Vertex3 eye = cam->getEye();
			Vertex3 centre = cam->getCentre();
			Vertex3 up = cam->getUp();

			eye.x += lx * scalar;
			eye.z += lz * scalar;			
			centre.x += lx * scalar;
			centre.z += lz * scalar;
			cam->lookAt(eye.x, eye.y, eye.z, centre.x, centre.y, centre.z, up.x, up.y, up.z);

			break;
		}
	case GLUT_KEY_DOWN:
		{
			Camera* cam = Camera::getSingleton();
			//Get line of sight 
			double angle = cam->getAngle();
			double lx = sin(angle);
			double lz = -cos(angle);
			//Move both eye and lookAt along same path
			double scalar = 0.1;
			Vertex3 eye = cam->getEye();
			Vertex3 centre = cam->getCentre();
			Vertex3 up = cam->getUp();
			eye.x -= lx * scalar;
			eye.z -= lz * scalar;
			
			centre.x -= lx * scalar;
			centre.z -= lz * scalar;
			cam->lookAt(eye.x, eye.y, eye.z, centre.x, centre.y, centre.z, up.x, up.y, up.z);
			break;
		}
	default:
		break;
	}
}