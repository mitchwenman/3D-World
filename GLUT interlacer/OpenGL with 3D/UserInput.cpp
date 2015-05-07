#include "UserInput.h"
#include "libs\glew.h"
#include "libs\glut.h"
#include "Camera.h"
#include "CameraUtil.h"
#include <math.h>
#include "World.h"
#include "ObjectTransform.h"

void UserInput::handleKeyInput(unsigned char c, int x, int y)
{
	switch (c)
	{
	case '\t':
		{
			World::getInstance()->toggleSelectedObject();
			break;
		}
	case 'w':
		{
			World *world = World::getInstance();
			int selectedPolygonIndex = world->getSelectedObjectIndex();
			if (selectedPolygonIndex != -1)
			{
				WorldObject *object = world->objects[selectedPolygonIndex];
				ObjectTransform::translateObject(object, 0.0, 0.0, -0.1);
			}
			break;
		}
	case 's':
		{
			World *world = World::getInstance();
			int selectedPolygonIndex = world->getSelectedObjectIndex();
			if (selectedPolygonIndex != -1)
			{
				WorldObject *object = world->objects[selectedPolygonIndex];
				ObjectTransform::translateObject(object, 0.0, 0.0, 0.1);
			}
			break;
		}
	case 'a':
		{
			World *world = World::getInstance();
			int selectedPolygonIndex = world->getSelectedObjectIndex();
			if (selectedPolygonIndex != -1)
			{
				WorldObject *object = world->objects[selectedPolygonIndex];
				ObjectTransform::translateObject(object, -0.1, 0.0, 0.0);
			}
			break;
		}
	case 'd':
		{
			World *world = World::getInstance();
			int selectedPolygonIndex = world->getSelectedObjectIndex();
			if (selectedPolygonIndex != -1)
			{
				WorldObject *object = world->objects[selectedPolygonIndex];
				ObjectTransform::translateObject(object, 0.1, 0.0, 0.0);
			}
			break;
		}
	case 'e':
		{
			World *world = World::getInstance();
			int selectedPolygonIndex = world->getSelectedObjectIndex();
			if (selectedPolygonIndex != -1)
			{
				WorldObject *object = world->objects[selectedPolygonIndex];
				ObjectTransform::translateObject(object, 0.0, 0.1, 0.0);
			}
			break;
		}
	case 'f':
		{
			World *world = World::getInstance();
			int selectedPolygonIndex = world->getSelectedObjectIndex();
			if (selectedPolygonIndex != -1)
			{
				WorldObject *object = world->objects[selectedPolygonIndex];
				ObjectTransform::translateObject(object, 0.0, -0.1, 0.0);
			}
			break;
		}
	default:
		break;
	}
}

void UserInput::handleSpecialKeyInput(unsigned char c, int x, int y)
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
			break;
		}
	default:
		break;
	}
}