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
			double angle = asin(cam->center.x - cam->eye.x);
			//Decrease angle
			double newAngle = angle - 0.1;
			//Calculate new line of sight
			double lx = sin(newAngle);
			double lz = -cos(newAngle);
			//Add values to lookAt
			cam->center.x = cam->eye.x + lx;
			cam->center.z = cam->eye.z + lz;
			break;
		}
	case GLUT_KEY_RIGHT:
		{
			Camera* cam = Camera::getSingleton();
			//Get current angle
			double angle = asin(cam->center.x - cam->eye.x);
			//Increase angle
			double newAngle = angle + 0.1;
			//Calculate new line of sight
			double lx = sin(newAngle);
			double lz = -cos(newAngle);
			//Add values to lookAt
			cam->center.x = cam->eye.x + lx;
			cam->center.z = cam->eye.z + lz;
			break;
		}
	default:
		break;
	}
}