#pragma once

#include "libs\glm\glm.hpp"
#include "GraphicsUtil.h"
#include "Transformation.h"
#include "WaveFrontPolygon.h"

//! A class representing a bounding sphere that can be used for collision detection.
/*!
	This class is used to represent a bounding sphere that can be used for collision
	detection for any arbitrary object. The class can generate a bounding sphere for a polygon,
	or it can be used to store a precalculated centre point and radius.
*/
class BoundingSphere
{

public:	
	//! The radius of the bounding sphere.
	double radius;

	//! The centre point of the bounding sphere.
	glm::vec3 centrePoint;

	//! Tests whether the bounding sphere collides with another bounding sphere. This is calculated
	//! by checking if the sum of the radii is greater than the distance between the two centre points.
	/*!
		Pseudocode:
		@vertbatim
			radiiSum = this.radius + otherSphere.radius
			return (otherSphere.centrePoint - this.centrePoint < radiiSum)
		@endverbatim
	*/
	//! @param otherSphere The other sphere which potentionally intersects/collides with this bounding sphere.
	//! @return True if otherSphere collides with this bounding sphere, else false.
	bool collides(BoundingSphere otherSphere);

	//! Creates a default bounding sphere with an uninitalised radius and centre point.
	BoundingSphere() {};

	//! Creates a bounding sphere with a precaculated centre point and radius.
	//! @param center The centre point vector of the bounding sphere.
	//! @param radius The radius of the new bounding sphere.
	BoundingSphere(glm::vec3 center, double radius) : centrePoint(center), radius(radius) {};

	//! Creates a bounding sphere by calculating the centre point and radius of a given polygon.
	//! Uses a bounding box to find the centre. The vertex from the bounding box with the greatest distance from the centre point
	//! is used to calculate the radius.
	/*!
		Pseudocode:
		@verbatim
			box = createBoundingBox(polygon)
			centre = box.center
			maxXCoordinateDist = max(box.minXCoordFromCenter, box.maxXCoordFromCenter)
			maxYCoordinateDist = max(box.minYCoordFromCenter, box.maxYCoordFromCenter)
			maxZCoordinateDist = max(box.minZCoordFromCenter, box.maxZCoordFromCenter)

			maxCoordFromCenter = max(maxXCoordinateDist, maxYCoordinateDist, maxZCoordinateDist)
			radius = magnitude(maxCoordFromCenter)
		@endverbatim	
	*/
	//! @param polygon The polygon that the bounding sphere will be calculated from.
	BoundingSphere(WaveFrontPolygon polygon);

};


//! Extends BoundingSphere by allow the radius and centre point to be transformed.
/*!
	This class extends BoundingSphere by providing the ability to transform the centre point
	and radius by a set of transformations. This is useful as the same set of transformations that are applied
	to an object each time it is drawn can also be applied to its bounding sphere, ensuring that collision detection
	operations are relative to the object's position in world space.
*/
class TransformableBoundingSphere : public BoundingSphere
{
private:
	//! The centre point of the bounding sphere in world space.
	glm::vec3 worldSpaceCentrePoint;

	//! The radius of the bounding sphere in world space. This is different
	//! to radius if a scale operation has been applied to it.
	double worldRadius;

	//! The matrix that transforms the bounding sphere from world space into object space.
	glm::mat4 worldMatrix;

public:
	//! Creates a TransformableBoundingSphere from an arbitrary polygon. Calls the parent function with the same signature
	//! and initialises the worldMatrix to the identity matrix.
	TransformableBoundingSphere(WaveFrontPolygon polygon);

	//! Creates an empty TransformableBoundingSphere without setting member variables.
	TransformableBoundingSphere() {};

	//! Transforms the worldMatrix, radius and centre point of the bounding sphere and sets these values in
	//! worldRadius and worldSpaceCentrePoint. 
	/*! Pseudocode:
		@verbatim
		worldRadius = radius
		worldCenterPoint = centerPoint
		for (each transformation)
			if (TRANSLATE)
				translate(worldMatrix)
			else if (SCALE)
				scale(worldRadius)
			else if (ROTATE)
				rotate(worldMatrix)
			worldCenterPoint = worldMatrix * centerPoint
		@endverbatim
	*/
	//! @param transforms The set of transforms to be applied to the bounding sphere.
	void setTransform(std::vector<Transformation *> transforms);

	//! Produces a BoundingSphere from the current worldRadius and worldSpaceCentrePoint values. This object
	//! is created on the heap and must be deleted by the caller. The produced object can be used in collision detection.
	BoundingSphere* transform(); 
};