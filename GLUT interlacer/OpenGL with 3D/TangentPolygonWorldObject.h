#pragma once

#include "WorldObject.h"
#include "TangentWaveFrontPolygon.h"
#include "BoundingSphere.h"

//! A wrapper around an abitrary TangentWaveFrontPolygon object that has been loaded from file.
/*!
	This class should be used together with a Normal Map shader program.
*/
class TangentPolygonWorldObject : public WorldObject
{
private:
	//! The WaveFrontPolygon object that will be drawn.
	TangentWaveFrontPolygon *polygon;
	
public:
	//! Simply sets the provided parameters and initialises the object's bounding sphere.
	//! @param polygon The polygon that will be drawn.
	//! @param shaderProgram The shader program that will be used to render the object.
	//! @param trans The transformations that will be applied to the model view matrix prior to rendering the object.
	TangentPolygonWorldObject(TangentWaveFrontPolygon* polygon,
						IShaderProgram* shaderProgram = NULL, 
						std::vector<Transformation*> trans = std::vector<Transformation*>()); 


	//! Applies the transformations to model view matrix and renders polygon to the screen using shaderProgram.
	//! @sideeffect If animations are present in the transformations vector then the transformation values may be modified if the animation is due to trigger.
	void draw();

	//! Tests whether this polygon collides with another object using bounding spheres.
	/*!
		Pseudocode:
		@verbatim
			thisBoundingSphere.setTransformations(this.transformations)
			objectBoundingSphere.setTranformations(objectTransformations)
			thisTransformedSphere = thisBoundingSphere.transform()
			objectTransformedSphere = objectBoundingSphere.transform()
			return collides(thisTransformedSphere, objectTransformedSphere)
		@endverbatim
	*/
	//! @param object The other object to be tested for a collision.
	//! @return True if the object collides with this polygon, else false.
	bool collides(WorldObject *object);

};