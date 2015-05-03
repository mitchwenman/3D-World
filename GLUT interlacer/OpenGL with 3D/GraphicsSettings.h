#pragma once

#include "libs\glew.h"
#include "libs\glm\glm.hpp"
#include "GraphicsUtil.h"

class GraphicsSettings
{
public:
	Vertex2 frameDimensions; /**< The window dimensions */



	glm::mat4 modelViewMatrix; /**< The current model view matrix */

	glm::mat4 projectionViewMatrix; /**< The current projection matrix */

	///Resets the current model view matrix to identity.
	///Sets GL_MODELVIEW to identity
	void resetModelView(); 

	///Resets the current projection view matrix to identity
	///Sets GL_PROJECTION to identity.
	void resetProjectionView();

	///
	///Sets the open gl matrices to the current model view/projection matrices
	void setGLMatrices();

	///Sets the window dimension variables
	///@param x The x dimension
	///@param y The y dimension
	void setFrameDimensions(int x, int y) { frameDimensions.x = x; frameDimensions.y = y; }

	///Gets the graphics settings singleton object
	///@return The singleton object.
	static GraphicsSettings* getSingleton();

private:
	///
	///Private constructor for the singleton pattern
	///Sets up both matrices
	GraphicsSettings();

};