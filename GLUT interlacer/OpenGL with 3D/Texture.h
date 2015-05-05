#pragma once

#include <string>
#include "libs\glew.h"
#include "libs\glut.h"

#include <vector>

/*
	Loosely based on this tutorial: http://ogldev.atspace.co.uk/www/tutorial16/tutorial16.html
*/

class Texture
{
public:
	///Constructor
	///@param textureTarget TEXTURE_2D, TEXTURE_3D etc.
	///@param file The BMP file of the texture.
	Texture(GLenum textureTarget, std::string file);

	///Binds this texture to the active texture GL_TEXTURE0
	void bind(GLenum textureUnit);

private:
	//! The id given to the texture by openGL
	GLuint textureID;

	//! The openGL texture target. TEXTURE_2D etc.
	GLenum textureTarget;

	//! The texture data blob that openGL will use to generate the texture.
	std::vector<unsigned char> textureData;

	//! Number of rows, number of columns in image
	int rows, columns;

	///Loads a BMP and generates a texture from it .
	///@param file The BMP image.
	void loadFromPath(std::string file);

	

};