#include "ModelTransform.h"
#include "libs\glut.h"
#include "libs\glm\glm.hpp"
#include "libs\glm\gtc\matrix_transform.hpp"
#include "libs\glm\gtc\type_ptr.hpp"


void ModelTransform::translate(double x, double y, double z)
{
	glMatrixMode(GL_MODELVIEW);
	glm::mat4 translate = glm::translate(glm::mat4(1.0), glm::vec3(x, y, z));
	glMultMatrixf(glm::value_ptr(translate));
}