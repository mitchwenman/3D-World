#pragma once

#include "libs\glew.h"
#include "libs\glm\glm.hpp"
#include "GraphicsUtil.h"

//! A small wrapper class responsible for setting the openGL model view and projection matrices.
class GraphicsSettings
{
public:
	//! The dimensions of the window.
	Vertex2 frameDimensions;

	//! The current model view matrix. This may not necessarily be equal to the projection matrix held by openGL.
	glm::mat4 modelViewMatrix; 

	//! The current projection matrix. This may not necessarily be equal to the projection matrix held by openGL.
	glm::mat4 projectionViewMatrix; 

	//! Global option for whether bounding spheres for objects should be drawn.
	bool drawBoundingSphere;

	//! Resets the current model view matrix to identity. Also sets GL_MODELVIEW to identity.
	//! @sideeffect The openGL model view matrix is set to the identity matrix.
	void resetModelView(); 

	//! Resets the current projection view matrix to identity.
	//! @sideeffect The openGL projection matrix is set to the identity matrix.
	void resetProjectionView();


	//! Sets the open gl matrices to the current model view/projection matrices.
	//! @sideeffect All future draw calls will be made using this object's matrices, until calls to reset*View() are made.
	void setGLMatrices();

	//! Sets the window dimension variables.
	//! @param x The x dimension
	//! @param y The y dimension
	void setFrameDimensions(int x, int y) { frameDimensions.x = x; frameDimensions.y = y; }

	//! Gets the graphics settings singleton object
	//! @return The singleton object.
	static GraphicsSettings* getSingleton();

private:
	//!  Private constructor for the singleton pattern. Initialises the model and projection matrices to identity.
	GraphicsSettings();

};