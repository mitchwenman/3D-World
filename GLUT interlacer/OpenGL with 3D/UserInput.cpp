#include "UserInput.h"
#include "libs\glew.h"
#include "libs\glut.h"
#include "Camera.h"
#include "CameraUtil.h"
#include <math.h>
#include "World.h"
#include "WorldObject.h"
#include "Transformation.h"

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
			break;
		}
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
				std::vector<Transformation *> objectTransformations = object->transformations;
				Transformation *translateTrans = NULL;
				//Find first transformation that is a translate
				unsigned int i;
				for (i = 0; i < objectTransformations.size(); i++)
				{
					if (objectTransformations[i]->type == TRANSLATE)
					{
						translateTrans = objectTransformations[i];
						break;
					}
				}
				if (translateTrans == NULL)
				{
					Vertex4 values = { 0, 0, 0, 0 };
					translateTrans = new Transformation(TRANSLATE, values);
				}					
				//Add -z value to translation
				translateTrans->values.z -= 0.1;
				//Add to transformation list if wasn't in there before
				if (i == objectTransformations.size())
				{
					objectTransformations.push_back(translateTrans);
				} 
				object->transformations = objectTransformations;
			}
			break;
		}
	default:
		break;
	}
}