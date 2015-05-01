#pragma once

#include <string>
#include "libs\glew.h"
#include "libs\glut.h"

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

	GLuint textureID;

	GLenum textureTarget;

	unsigned char* textureData;

	//number of rows, number of columns in image
	int rows, columns;

	///Loads a BMP and generates a texture from it .
	///@param file The BMP image.
	void loadFromPath(std::string file);

	

};