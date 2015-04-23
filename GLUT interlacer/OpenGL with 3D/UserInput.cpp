#include "UserInput.h"
#include "libs\glew.h"
#include "libs\glut.h"
#include "Camera.h"
#include "CameraUtil.h"
#include <math.h>

void UserInput::handleKeyInput(unsigned char c, int x, int y)
{
	switch (c)
	{
	case GLUT_KEY_LEFT:
		{
			Camera* cam = Camera::getSingleton();
			CameraUtil::RotateCamera(cam, -0.1);
			break;
		}
	case GLUT_KEY_RIGHT:
		{
			Camera* cam = Camera::getSingleton();
			CameraUtil::RotateCamera(cam, 0.1);
			break;
		}

	case GLUT_KEY_UP:
		{
			Camera* cam = Camera::getSingleton();
			CameraUtil::MoveCamera(cam, 0.1);

			break;
		}
	case GLUT_KEY_DOWN:
		{
			Camera* cam = Camera::getSingleton();
			CameraUtil::MoveCamera(cam, -.1);
		}
	default:
		break;
	}
}