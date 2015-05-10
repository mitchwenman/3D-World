#pragma once

#include "WorldObject.h"

namespace CollisionDetection
{
	bool objectCollidesWithWorld(WorldObject *object);

	bool camCollidesWithWorld();

	bool objectCollidesWithWalls(WorldObject *object);

	bool objectCollidesWithObjects(WorldObject *object);

};