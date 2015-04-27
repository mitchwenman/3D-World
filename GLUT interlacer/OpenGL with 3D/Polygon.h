#include "WorldObject.h"
#include "WaveFrontPolygon.h"

class PolygonWorldObject : public WorldObject
{
private:
	WaveFrontPolygon* polygon;

public:
	PolygonWorldObject(WaveFrontPolygon* polygon, MaterialData* material, 
				unsigned int shaderProgram = 0, 
				std::vector<Transformation*> trans = std::vector<Transformation*>()) : WorldObject(material, shaderProgram, trans) { this->polygon = polygon; };


	void draw();
};