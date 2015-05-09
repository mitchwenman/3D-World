#include "CollisionDetection.h"
#include "World.h"

bool CollisionDetection::collidesWithWorld(WorldObject *object)
{
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
