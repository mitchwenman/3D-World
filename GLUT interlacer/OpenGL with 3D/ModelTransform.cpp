#include "ModelTransform.h"
#include "libs\glew.h"
#include "libs\glut.h"
#include "libs\glm\glm.hpp"
#include "libs\glm\gtc\matrix_transform.hpp"
#include "libs\glm\gtc\type_ptr.hpp"
#include "GraphicsSettings.h"


void ModelTransform::translate(double x, double y, double z)
{
	GraphicsSettings *gset = GraphicsSettings::getSingleton();	
	glm::mat4 translation = glm::translate(gset->modelViewMatrix, glm::vec3(x, y, z));
	gset->modelViewMatrix = translation;

}

void ModelTransform::rotate(float angle, double x, double y, double z)
{
	GraphicsSettings *gset = GraphicsSettings::getSingleton();
	gset->modelViewMatrix = glm::rotate(gset->modelViewMatrix, float(angle * (3.14/180)), glm::vec3(x, y, z));
	
}

void ModelTransform::scale(double x, double y, double z)
{
	GraphicsSettings *gset = GraphicsSettings::getSingleton();
	gset->modelViewMatrix = glm::scale(gset->modelViewMatrix, glm::vec3(x, y, z));
}