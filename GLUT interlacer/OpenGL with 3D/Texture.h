#pragma once

#include <string>
#include "libs\glew.h"
#include "libs\glut.h"

class Texture
{
public:
	Texture(GLenum textureTarget, std::string file);

private:

	GLuint textureID;

	unsigned char* textureData;

	//number of rows, number of columns
	int textureU, textureV;

	bool loadFromPath(std::string file);

	void bind();

};