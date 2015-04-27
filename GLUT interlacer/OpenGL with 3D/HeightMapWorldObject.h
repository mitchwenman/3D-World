#include "WorldObject.h"
#include "HeightMap.h"

class HeightMapWorldObject : public WorldObject
{
private:
	HeightMap* heightmap;

public:
	HeightMapWorldObject(HeightMap* hm, MaterialData* material, 
				unsigned int shaderProgram = 0, 
				std::vector<Transformation*> trans = std::vector<Transformation*>()) : WorldObject(material, shaderProgram, trans) { this->heightmap = hm; };


	void draw();
}