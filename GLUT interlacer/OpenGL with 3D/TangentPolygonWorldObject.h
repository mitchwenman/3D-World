#pragma once

#include "WorldObject.h"
#include "TangentWaveFrontPolygon.h"

class TangentPolygonWorldObject : public WorldObject
{
private:
	TangentWaveFrontPolygon *polygon;

public:
	TangentPolygonWorldObject(TangentWaveFrontPolygon* polygon,
						IShaderProgram* shaderProgram = NULL, 
						std::vector<Transformation*> trans = std::vector<Transformation*>()) : WorldObject(shaderProgram, trans) { this->polygon = polygon; };


	void draw();

};