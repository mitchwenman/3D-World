#pragma once

#include "libs\glew.h"
#include "libs\glm\glm.hpp"
#include "GraphicsUtil.h"

class GraphicsSettings
{
public:
	Vertex2 frameDimensions;



	glm::mat4 modelViewMatrix;

	glm::mat4 projectionViewMatrix;

	void resetModelView() { modelViewMatrix = glm::mat4(); }

	void resetProjectionView() { projectionViewMatrix = glm::mat4(); }

	//Sets the open gl matrices to the current model view/projection matrices
	void setGLMatrices();

	void setFrameDimensions(int x, int y) { frameDimensions.x = x; frameDimensions.y = y; }

	static GraphicsSettings* getSingleton();

private:
	GraphicsSettings();

};