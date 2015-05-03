#include "Texture.h"
#include "libs\CImg.h"

#include "libs\glew.h"
#include "libs\glut.h"

#include <vector>

Texture::Texture(GLenum textureTarget, std::string file) : textureTarget(textureTarget)
{
	loadFromPath(file);

}


void Texture::loadFromPath(std::string path)
{
	cimg_library::CImg<unsigned char> image(path.c_str());
	rows = image.height();		
	columns = image.width();
	//CIMG stores in band sequential format
	textureData.reserve(rows * columns * 3);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			textureData.push_back(*image.data(i, j, 0, 0));
			textureData.push_back(*image.data(i, j, 0, 1));
			textureData.push_back(*image.data(i, j, 0, 2));
		}		
	}




	//Generate texture 
	glGenTextures(1, &this->textureID);	
	glBindTexture(this->textureTarget, this->textureID);
	
	glTexImage2D(this->textureTarget, 0, GL_RGB, columns, rows, 0, GL_RGB, GL_UNSIGNED_BYTE, this->textureData.data()); 
}

void Texture::bind(GLenum textureUnit)
{	
	glActiveTexture(textureUnit);
	glBindTexture(this->textureTarget, this->textureID);
	//clamp to 0, 1 on x and y
	glTexParameteri(this->textureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(this->textureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(this->textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(this->textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}