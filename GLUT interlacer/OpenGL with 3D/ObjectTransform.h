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
	/*
		Pseudocode:
		@verbatim
			Transformation translate
			i = object.transformations.TranslateTransformIndex
			if (i == object.transformations.size)
				translate = new Transformation(TRANSLATE, vec4(0))
				object.transformations.insertAtIndex(0, translate)
			else
				translate = object.transformations[i]
			translate += vec4(dx, dy, dz, 0)
			if (objectCollidesWithWorld(object))
				translate -= vec4(dx, dy, dz, 0)
		@endverbatim
	*/
	//! @param object The object to be modified.
	//! @param dx The x axis translation.
	//! @param dy The y axis translation.
	//! @param dz The z axis translation.
	void translateObject(WorldObject *object, double dx, double dy, double dz);

	//! Adds a (or modifies an existing) rotation transformation to an object.
	/*
		Pseudocode:
		@verbatim
			Transformation rotate
			i = object.transformations.TranslateTransformIndex
			if (i == object.transformations.size)
				rotate = new Transformation(ROTATE, vec4(0))
				object.transformations.insertBack(rotate)
			else
				rotate = object.transformations[i]
			rotate += vec4(angle, dx, dy, dz)
			if (objectCollidesWithWorld(object))
				if (rotate = vec4(angle, dx, dy, dz)) 
					object.transformations.erase(i)
				else
					rotate -= vec4(angle, dx, dy, dz)
		@endverbatim
	*/
	//! @param object The object to be modified.
	//! @param dx The x axis rotation.
	//! @param dy The y axis rotation.
	//! @param dz The z axis rotation.
	void rotateObject(WorldObject *object, double angle, double dx, double dy, double dz);

	//! Adds a (or modifies an existing) scale transformation to an object.
	/*
		Pseudocode:
		@verbatim
			Transformation scale
			i = object.transformations.TranslateTransformIndex
			if (i == object.transformations.size)
				rotate = new Transformation(scale, vec4(1.0))
				object.transformations.insertBack(scale)
			else
				scale = object.transformations[i]
			scale = componentMultiply(scale, vec4(dx, dy, dz, 0))
			if (objectCollidesWithWorld(object))
				scale = componentDivide(scale, vec4(dx, dy, dz, 1))
		@endverbatim
	*/
	//! @param object The object to be modified.
	//! @param dx The x axis scale factor.
	//! @param dy The y axis scale factor.
	//! @param dz The z axis scale factor.
	void scaleObject(WorldObject *object, double sx, double sy, double sz);

};