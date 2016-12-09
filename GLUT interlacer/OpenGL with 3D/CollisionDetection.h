#pragma once

#include "WorldObject.h"

//! A namespace for grouping together collision detection functions.
/*!
	This namespace groups together functions for detecting collisions between the world (including the camera). 
	The functions simply iterate over the list of collidable objects and invoke the object's collide() method to test
	if it collides with another object.
*/
namespace CollisionDetection
{
	//! Tests if a particular object collides with any object in the game world, including
	//! walls, polygons and the camera.
	/*!
		Pseudocode:
		@verbatim
			if (!objectCollidesWithWorld() && !objectCollidesWithCamera() && !objectCollidesWithObjects())
				return false
			else
				return true
		@endverbatim
	*/
	//! @param object The object that potentially collides with the world and will be tested.
	//! @returns True if the object collides with any other object, otherwise false.
	bool objectCollidesWithWorld(WorldObject *object);

	//! Tests if the camera collides with any other object in the world.
	//! @returns True if the camera collides with any object in the world, otherwise false.
	bool cameraCollidesWithWorld();

	//! Tests if an object collides with any wall in the world's Maze.
	/*!
		Pseudocode:
		@verbatim
			for (each wall in Maze)
				if (wall.collides(object))
					return true
			return false
		@endverbatim
	*/
	//! @param object The object to be tested for collisions in the Maze.
	//! @return True if the object collides with a wall in the maze, otherwise false.
	bool objectCollidesWithWalls(WorldObject *object);

	//! Tests if an object collides with any other polygon in the world (does not include world walls)
	/*!
		Pseudocode:
		@verbatim
			for (each polygon in World)
				if (polygon.collides(object))
					return true
				return false
		@endverbatim
	*/
	//! @param object The object to be tested for collisions.
	//! @return True if the object collides with another polygon, otherwise false.
	bool objectCollidesWithObjects(WorldObject *object);

	//! Tests if an object collides with the current position of the camera.
	//! @param object The object that will be tested for a collision with the camera.
	//! @return True if the object collides with the camera, else false.
	bool objectCollidesWithCamera(WorldObject *object);

};