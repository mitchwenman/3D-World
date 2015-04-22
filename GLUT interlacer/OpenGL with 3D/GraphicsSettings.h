#pragma once

#include "libs\glm\glm.hpp"

class GraphicsSettings
{
public:
	glm::mat4 modelViewMatrix;

	glm::mat4 projectionViewMatrix;

	void resetModelView() { modelViewMatrix = glm::mat4(); }

	void resetProjectionView() { projectionViewMatrix = glm::mat4(); }

	static GraphicsSettings* getSingleton();

private:
	GraphicsSettings();

};