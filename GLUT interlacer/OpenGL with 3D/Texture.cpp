#include "Texture.h"
#include "libs\CImg.h"

#include "libs\glew.h"
#include "libs\glut.h"

Texture::Texture(GLenum textureTarget, std::string file) : textureTarget(textureTarget)
{
	loadFromPath(file);

}


bool Texture::loadFromPath(std::string path)
{
	cimg_library::CImg<unsigned char> image(path.c_str());
	rows = image.height();		
	columns = image.width();

	this->textureData = image.data();
	//Generate texture 
	glGenTextures(1, &this->textureID);	
	glBindTexture(this->textureTarget, this->textureID);
	
	glTexImage2D(this->textureTarget, 0, GL_RGB, columns, rows, 0, GL_RGB, GL_UNSIGNED_BYTE, this->textureData); 
	GLenum err = glGetError();
	return true;
}

void Texture::bind()
{	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(this->textureTarget, this->textureID);
	//clamp to 0, 1 on x and y
	glTexParameteri(this->textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(this->textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(this->textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(this->textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}