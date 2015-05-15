#include "Game.h"

static Game* _instance;

Game* Game::getInstance()
{
	if (!_instance)
		_instance = new Game();
	return _instance;
}

bool Game::insideBoundary(Vertex3 position)
{
	return position.x > minX && position.x < maxX &&
			position.z > minZ && position.z < maxZ;
}