#include "SpecularNormalMap.h"
#include "ShaderLoader.h"
#include "DirectionalLight.h"
#include "Camera.h"
#include "libs\glm\glm.hpp"
#include "libs\glm\gtc\type_ptr.hpp"

#include "libs\glew.h"
#include "libs\glut.h"

SpecularNormalMap::SpecularNormalMap(std::string texture, std::string normalMap)
{
	this->texture = new Texture(GL_TEXTURE_2D, texture);
	this->normalMap = new Texture(GL_TEXTURE_2D, normalMap);

	this->programId = ShaderLoader::link(ShaderLoader::compile("texture_normal.vs", GL_VERTEX_SHADER),
		ShaderLoader::compile("texture_normal.fs", GL_FRAGMENT_SHADER));
}

void SpecularNormalMap::useProgram()
{
	//Texture sampler
	texture->bind(GL_TEXTURE0);
	glUseProgram(this->programId);
	int samplerLocation = glGetUniformLocation(this->programId, "gSampler"); 
	glUniform1i(samplerLocation, 0);

	//Normal Map
	normalMap->bind(GL_TEXTURE1);
	int normalSamplerLocation = glGetUniformLocation(this->programId, "gNormalSampler");
	glUniform1i(normalSamplerLocation, 1);

	//Setting light direction uniform
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