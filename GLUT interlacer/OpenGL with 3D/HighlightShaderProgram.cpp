#include "HighlightShaderProgram.h"
#include "ShaderLoader.h"
#include "DirectionalLight.h"
#include "Camera.h"

#include "libs\glm\glm.hpp"
#include "libs\glm\gtc\type_ptr.hpp"

#include "libs\glew.h"
#include "libs\glut.h"

HighlightShaderProgram::HighlightShaderProgram()
{
	this->programId = ShaderLoader::link(ShaderLoader::compile("selected_poly.vs", GL_VERTEX_SHADER),
		ShaderLoader::compile("selected_poly.fs", GL_FRAGMENT_SHADER));
}

void HighlightShaderProgram::useProgram()
{
	glUseProgram(this->programId);

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