#pragma once

#include "MaterialData.h"
#include "Transformation.h"
#include "IShaderProgram.h"
#include "BoundingSphere.h"
#include <vector>

//! Defines an interface for a generic wrapper for extra information about a polygon.
/*!
	A subclass should manage the storage of the type of polygon, as well as implement the draw method.
*/
class WorldObject
{
public:

	//! The set of model view transformations that should be applied prior to drawing,
	//! although this is ultimately left up to the subclass.
	std::vector<Transformation*> transformations;

	//! The shader program to be used when drawing the object.
	IShaderProgram* shaderProgram;

	TransformableBoundingSphere boundingSphere;
	
	//! Virtual method to draw the object. To be implemented by the subclass.
	virtual void draw() = 0;

	//! Virtual method to test whether this object in world space collides with another. To be implemented by sub class.
	virtual bool collides(WorldObject* object) = 0;

	//! Constructor for the object. Simply sets the given values.
	//! @param shaderProgram The shader program to be used to draw the object.
	//! @param trans The set of model view transformations to be applied prior to drawing.
	WorldObject(IShaderProgram* shaderProgram = NULL, 
				std::vector<Transformation*> trans = std::vector<Transformation*>()) : shaderProgram(shaderProgram),
																						transformations(trans) {};
	

};