#include "WorldObject.h"
#include "HeightMap.h"

class HeightMapWorldObject : public WorldObject
{
private:
	HeightMap* heightmap;

public:
	HeightMapWorldObject(HeightMap* hm, IShaderProgram* shaderProgram = NULL, 
				std::vector<Transformation*> trans = std::vector<Transformation*>()) : WorldObject(shaderProgram, trans) { this->heightmap = hm; };


	void draw();
};