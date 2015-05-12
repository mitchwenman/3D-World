#pragma once

#include "IShaderProgram.h"

//! Extends IShaderProgram. A shader program used to highlight an object on the screen.
/*
	This shader program is used by the World class to indicate which object is currently selected by the user.
*/
class HighlightShaderProgram : public IShaderProgram
{
public:
	//! Constructor for the shader program. Loads the vertex and fragment shader.
	HighlightShaderProgram();

	//! Invokes glUseProgram. Sets the camera matrix and light direction uniforms.
	void useProgram();
};