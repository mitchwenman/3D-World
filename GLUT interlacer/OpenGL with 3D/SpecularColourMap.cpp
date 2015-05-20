///////////////////////////////////////////////////////////////////////////////////
// Filename: SpecularColourMap.cpp
// Author: Mitch Wenman
// Date Modified: 20/05/2015
// Description: Loads the opengl shader for specular lighting with textures.
///////////////////////////////////////////////////////////////////////////////////

// ============== INCLUDES =================//
#include "SpecularColourMap.h"
#include "DirectionalLight.h"
#include "Camera.h"
#include "libs\glm\glm.hpp"
#include "libs\glm\gtc\type_ptr.hpp"
#include "ShaderLoader.h"
#include "libs\glew.h"
#include "libs\glut.h"

// ============== FUNCTIONS =================//
SpecularColourMap::SpecularColourMap(std::string file)
{
	this->texture = new Texture(GL_TEXTURE_2D, file); //Load texture from file	

	this->programId = ShaderLoader::link(ShaderLoader::compile("texture_specular.vs", GL_VERTEX_SHADER),
		ShaderLoader::compile("texture_specular.fs", GL_FRAGMENT_SHADER));
}

void SpecularColourMap::useProgram()
{
	//Texture sampler
	texture->bind(GL_TEXTURE0);
	glUseProgram(this->programId);
	int samplerLocation = glGetUniformLocation(this->programId, "gSampler"); 
	glUniform1i(samplerLocation, 0);

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