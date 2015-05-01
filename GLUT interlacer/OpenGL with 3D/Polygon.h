#include "WorldObject.h"
#include "WaveFrontPolygon.h"

class PolygonWorldObject : public WorldObject
{
private:
	WaveFrontPolygon* polygon;

public:
	PolygonWorldObject(WaveFrontPolygon* polygon,
						IShaderProgram* shaderProgram = NULL, 
						std::vector<Transformation*> trans = std::vector<Transformation*>()) : WorldObject(shaderProgram, trans) { this->polygon = polygon; };


	void draw();
};