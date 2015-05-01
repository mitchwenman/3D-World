#include "SpecularColourMap.h"
#include "DirectionalLight.h"
#include "Camera.h"
#include "libs\glm\glm.hpp"
#include "libs\glm\gtc\type_ptr.hpp"
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

	//Camera matrix
	Camera* cam = Camera::getSingleton();
	glm::mat4 cameraMatrix = cam->getLookAtMatrix();
	int camMatrixLocation = glGetUniformLocation(this->programId, "gCameraMatrix");
	glUniformMatrix4fv(camMatrixLocation, 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}