#pragma once

#include "WorldObject.h"
#include "TangentWaveFrontPolygon.h"

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
	//! Constructor for the object.
	//! @param polygon The polygon that will be drawn.
	//! @param shaderProgram The shader program that will be used to render the object.
	//! @param trans The transformations that will be applied to the model view matrix prior to rendering the object.
	TangentPolygonWorldObject(TangentWaveFrontPolygon* polygon,
						IShaderProgram* shaderProgram = NULL, 
						std::vector<Transformation*> trans = std::vector<Transformation*>()) : WorldObject(shaderProgram, trans) { this->polygon = polygon; };


	//! Applies the transformations to model view matrix and renders polygon to the screen using shaderProgram.
	void draw();

};