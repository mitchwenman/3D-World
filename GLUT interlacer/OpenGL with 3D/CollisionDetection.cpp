#include "CollisionDetection.h"
#include "World.h"
#include "Camera.h"
#include "GraphicsUtil.h"

bool CollisionDetection::collidesWithWorld(WorldObject *object)
{
	World *world = World::getInstance();

	//Check camera
	Camera* cam = Camera::getSingleton();
	glm::vec3 eye = GraphicsUtil::vertex3ToGLMVec3(cam->getEye());
	BoundingSphere *camSphere = new BoundingSphere(eye, 1);
	object->boundingSphere.setTransform(object->transformations);
	BoundingSphere *objSphere = object->boundingSphere.transform();
	bool collidesWithCam = camSphere->collides(*objSphere);
	delete(camSphere);
	delete(objSphere);
	if (collidesWithCam) 
		return true;
	//Check walls
	Maze *maze = world->maze;
	if (maze->collides(object))
		return true;
	
	//Check other objects
	std::vector<WorldObject*> objects = world->objects;
	unsigned int numCollisions = 0;
	for (std::vector<WorldObject*>::iterator it = objects.begin();
		it != objects.end(); it++)
	{
		if ((*it)->collides(object))
		{
			numCollisions++;
			if (numCollisions == 2) //The object will collide with itself
				break;
		}
	}
	return numCollisions == 2;
}
