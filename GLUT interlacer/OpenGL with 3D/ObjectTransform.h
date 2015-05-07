#pragma once

#include "WorldObject.h"

//! A namespace for grouping together world object transformation functions.
/*! 
	A namespace for grouping together functions which modify a world object's transformation properties, 
	allowing it to be moved, rotated and scaled by the user
*/
namespace ObjectTransform
{
	void translateObject(WorldObject *object, double dx, double dy, double dz);

}