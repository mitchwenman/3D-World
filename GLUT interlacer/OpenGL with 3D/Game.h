#pragma once

#include "GraphicsUtil.h"

//! A small wrapper class for defining the various metadata of the game world, for example, out of bounds areas.
class Game
{
public:
	//! Gets the singleton instance of the Game object.
	//! @return A pointer to the singleton instance of the game.
	static Game* getInstance();
	 
	//! Tests whether a vector is inside the bounds of the game world.
	/*!
		Pseudocode:
		@verbatim:
			return position.x > minX && position.x < maxX &&
					position.z > minZ && position.z < maxZ
		@endverbatim
	*/
	//! @return True if position is inside the world bounds, else false.
	bool insideBoundary(Vertex3 position);

private:
	//! The minimum boundary on the z axis
	double minZ;

	//! The maximum boundary on the z axis
	double maxZ;

	//! The minimum boundary on the x axis
	double minX;

	//! The maximum boundary on the x axis
	double maxX;

	//! A simple constructor for the game world. Sets the world boundaries.
	//! @sideeffect Invoking of this function will limit the camera's movement in the game world by the values defined internally in the constructor.
	Game() : minX(-3), maxX(20), minZ(-6.5), maxZ(9.5) {};


};