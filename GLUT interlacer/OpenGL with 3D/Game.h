#pragma once

#include "GraphicsUtil.h"

class Game
{
public:
	static Game* getInstance();

	bool insideBoundary(Vertex3 position);

private:
	
	double minZ, maxZ;
	double minX, maxX;

	Game() : minX(-3), maxX(20), minZ(-6.5), maxZ(9.5) {};


};