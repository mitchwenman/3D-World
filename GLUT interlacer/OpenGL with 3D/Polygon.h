#include "WorldObject.h"
#include "WaveFrontPolygon.h"

class Polygon : public WorldObject
{
private:
	WaveFrontPolygon* polygon;

public:
	Polygon(WaveFrontPolygon* polygon, MaterialData* material, 
				unsigned int shaderProgram = 0, 
				std::vector<Transformation*> trans = std::vector<Transformation*>()) : WorldObject(material, shaderProgram, trans) { this->polygon = polygon; };


	void draw();
}