#pragma once

#include "IShaderProgram.h"
#include "Texture.h"

#include <string>

//! A shader program that implements normal mapping with Phong lighting/shading.
class SpecularNormalMap : public IShaderProgram
{
private:
	//! The texture map used to colour the object.
	Texture* texture;

	//! The normal map with normal values stored in tangent space.
	Texture* normalMap;

public:
	//! Constructor for the object. Loads both the texture and normal map from file.
	//! @param texture The texture to be used for colouring the object.
	//! @param normalMap The image that will be used for the object's normals.
	SpecularNormalMap(std::string texture, std::string normalMap);

	//! Binds both texture files and invokes glUseProgram. Must be called prior to drawing the object.
	//! @sideeffect All future draw calls will use this program until another is specified.
	/*!
		Pseudocode:
		@verbatim
			bindTexture(colourMap)
			setSamplerUniform(colourMap)
			bindTexture(normalMap)
			setSamplerUniform(normalMap)
			setLightUniform()
			setCameraMatrixUniform()
		@endverbatim
	*/
	void useProgram();

};