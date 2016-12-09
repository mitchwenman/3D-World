#pragma once

#include "WorldObject.h"
#include "HeightMap.h"

//! A wrapper around a height map pointer.
/*!
	This class creates a wrapper around a height map pointer, allowing
	a set of transformations to be stored with the heightmap. This class also stores
	the shader program that is used to render the heightmap.
*/
class HeightMapWorldObject : public WorldObject
{
private:
	//! The heightmap that will be rendered. Must not be null.
	HeightMap* heightmap;

public:
	//! Constructor for the HeightMapWorldObject.
	//! @param hm The heightmap to be rendered.
	//! @param shaderProgram The shader program to be used when rendering hm. Defaults to 0.
	//! @param trans The transformations to be performed before rendering.
	HeightMapWorldObject(HeightMap* hm, IShaderProgram* shaderProgram = NULL, 
				std::vector<Transformation*> trans = std::vector<Transformation*>()) : WorldObject(shaderProgram, trans) { this->heightmap = hm; };


	//! Draws the heightmap to the screen.
	//! @sideeffect If animations are present in the transformations vector then the transformation values may be modified
	void draw();

	//! Tests whether an object collides with this heightmap. Always returns false.
	//! @param otherObject A pointer to the object to be tested for a collision.
	//! @return No collision detection is performed for height maps, so this always returns false.
	bool collides(WorldObject *otherObject) { return false; }
};