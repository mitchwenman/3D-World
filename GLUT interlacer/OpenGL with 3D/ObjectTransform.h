#pragma once

#include "WorldObject.h"

//! A namespace for grouping together world object transformation functions.
/*! 
	A namespace for grouping together functions which modify a world object's transformation properties, 
	allowing it to be moved, rotated and scaled by the user
*/
namespace ObjectTransform
{
	//! Adds a (or modifies an existing) translation transformation to an object.
	//! @param object The object to be modified.
	//! @param dx The x axis translation.
	//! @param dy The y axis translation.
	//! @param dz The z axis translation.
	void translateObject(WorldObject *object, double dx, double dy, double dz);

	//! Adds a (or modifies an existing) rotation transformation to an object.
	//! @param object The object to be modified.
	//! @param dx The x axis rotation.
	//! @param dy The y axis rotation.
	//! @param dz The z axis rotation.
	void rotateObject(WorldObject *object, double angle, double dx, double dy, double dz);

	//! Adds a (or modifies an existing) scale transformation to an object.
	//! @param object The object to be modified.
	//! @param dx The x axis scale factor.
	//! @param dy The y axis scale factor.
	//! @param dz The z axis scale factor.
	void scaleObject(WorldObject *object, double sx, double sy, double sz);

};