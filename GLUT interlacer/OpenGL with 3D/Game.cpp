///////////////////////////////////////////////////////////////////////////////////
// Filename: CameraUtil.cpp
// Author: Mitch Wenman
// Date Modified: 20/05/2015
// Description: Defines the current state of the game, including its boundaries.
///////////////////////////////////////////////////////////////////////////////////

// ============== INCLUDES =================//
#include "Game.h"

// ============== GLOBALS =================//
static Game* _instance;

// ============== FUNCTIONS =================//
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