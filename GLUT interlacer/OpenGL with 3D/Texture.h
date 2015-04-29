#pragma once

#include <string>
#include "libs\glew.h"
#include "libs\glut.h"

class Texture
{
public:
	Texture(GLenum textureTarget, std::string file);

	void bind();

private:

	GLuint textureID;

	GLenum textureTarget;

	unsigned char* textureData;

	//number of rows, number of columns in image
	int rows, columns;

	bool loadFromPath(std::string file);

	

};