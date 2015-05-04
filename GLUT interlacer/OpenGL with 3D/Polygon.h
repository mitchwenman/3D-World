#include "WorldObject.h"
#include "WaveFrontPolygon.h"

//! A class representing an arbitrary polygon.
class PolygonWorldObject : public WorldObject
{
private:
	//! The actual polygon to be rendered. Must not be null.
	WaveFrontPolygon* polygon;

public:

	//! Constructor the class.
	//! @param polygon The actual polygon to be rendered.
	//! @shaderProgram The shader program to be used when rendering the object.
	//! @param trans A set of transformations to be applied to the object before rendering.
	PolygonWorldObject(WaveFrontPolygon* polygon,
						IShaderProgram* shaderProgram = NULL, 
						std::vector<Transformation*> trans = std::vector<Transformation*>()) : WorldObject(shaderProgram, trans) { this->polygon = polygon; };

	//! Renders the polygon to the screen using the given shader program.
	//! First applies the set of transformations in transformations.
	void draw();
};