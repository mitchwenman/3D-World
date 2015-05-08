#include "WorldObject.h"
#include "HeightMap.h"

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
	void draw();

	//! Tests whether an object collides with this heightmap. Always returns false.
	//! @param otherObject A pointer to the object to be tested for a collision.
	//! @return No collision detection is performed for height maps, so this always returns false.
	bool collides(WorldObject *otherObject) { return false; }
};