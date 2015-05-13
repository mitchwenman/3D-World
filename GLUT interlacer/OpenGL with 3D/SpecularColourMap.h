#pragma once

#include "IShaderProgram.h"
#include "Texture.h"

#include <string>

//! A shader program that implements Phong lighting/shading with a simple 2D texture
class SpecularColourMap : public IShaderProgram
{
private:
	//! The texture that will be sampled to within the fragment shader
	//! to calculate the colour.
	Texture* texture;

public:
	//! Constructor for the object. Loads and creates the texture
	//! and loads the specular colour map vertex and fragment shaders.
	//! @param textureFile The texture image that will be used.
	SpecularColourMap(std::string textureFile);

	//! Binds the texture and invokes glUseProgram. Must be called prior to drawing the object.
	//! All future draw calls will use this program (until another is used).
	/*!
		Pseudocode:
		@verbatim
			bindTexture()
			passTextureSampler()
			passLightUniform()
			passCameraMatrix()
		@endverbatim
	*/
	void useProgram();
};