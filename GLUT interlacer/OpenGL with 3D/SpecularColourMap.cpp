#include "SpecularColourMap.h"
#include "DirectionalLight.h"
#include "ShaderLoader.h"
#include "libs\glew.h"
#include "libs\glut.h"


SpecularColourMap::SpecularColourMap(std::string file)
{
	Texture *texture = new Texture(GL_TEXTURE_2D, file);
	this->texture = texture;

	this->programId = ShaderLoader::link(ShaderLoader::compile("texture_specular.vs", GL_VERTEX_SHADER),
		ShaderLoader::compile("texture_specular.fs", GL_FRAGMENT_SHADER));
}

void SpecularColourMap::useProgram()
{
	texture->bind(GL_TEXTURE0);
	glUseProgram(this->programId);
	int samplerLocation = glGetUniformLocation(this->programId, "gSampler"); 
	glUniform1i(samplerLocation, 0);

	DirectionalLight *light = DirectionalLight::getSingleton();
	Vertex4 position = light->getDirection();
	int lightDirLocation = glGetUniformLocation(this->programId, "lightDirection");
	glUniform3f(lightDirLocation, -position.x, -position.y, -position.z);

	
}