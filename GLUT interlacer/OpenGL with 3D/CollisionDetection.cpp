#include "CollisionDetection.h"
#include "World.h"
#include "Camera.h"
#include "GraphicsUtil.h"

bool CollisionDetection::objectCollidesWithWorld(WorldObject *object)
{
	World *world = World::getInstance();

	//Check camera
	Camera* cam = Camera::getSingleton();
	glm::vec3 eye = GraphicsUtil::vertex3ToGLMVec3(cam->getEye());
	BoundingSphere camSphere = cam->boundingSphere;
	camSphere.centrePoint = eye;
	object->boundingSphere.setTransform(object->transformations);
	BoundingSphere *objSphere = object->boundingSphere.transform();
	bool collidesWithCam = camSphere.collides(*objSphere);
	delete(objSphere);
	if (collidesWithCam) 
		return true;
	//Check walls
	if (CollisionDetection::objectCollidesWithWalls(object))
		return true;
	
	//Check other objects
	if (CollisionDetection::objectCollidesWithObjects(object))
		return true;
	return false;
}

bool CollisionDetection::cameraCollidesWithWorld()
{
	Camera *cam = Camera::getSingleton();
	if (objectCollidesWithWalls(cam))
		return true;

	//Check other objects
	World *world = World::getInstance();
	std::vector<WorldObject*> objects = world->objects;
	unsigned int numCollisions = 0;
	for (std::vector<WorldObject*>::iterator it = objects.begin();
		it != objects.end(); it++)
	{
		if ((*it)->collides(cam))
		{
			return true;
		}
	}
	
	return false;
}

bool CollisionDetection::objectCollidesWithWalls(WorldObject *object)
{
	World *world = World::getInstance();
	Maze *maze = world->maze;
	if (maze->collides(object))
		return true;
}

bool CollisionDetection::objectCollidesWithObjects(WorldObject *object)
{
	//Check other objects
	World *world = World::getInstance();
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
