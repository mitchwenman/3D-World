#pragma once

#include "IShaderProgram.h"

class HighlightShaderProgram : public IShaderProgram
{
public:
	//! Constructor for the shader program. Loads the vertex and fragment shader.
	HighlightShaderProgram();

	//! Invokes glUseProgram. Sets the camera matrix and light direction uniforms.
	void useProgram();
};