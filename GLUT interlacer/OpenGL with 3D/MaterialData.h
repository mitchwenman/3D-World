#pragma once

#include "libs\glew.h"
#include "libs\glut.h"

class MaterialData
{
public:
	GLfloat specularColour[4];
	GLfloat diffuseColour[4];
	GLfloat ambientColour[4];
	GLfloat shininess[1];

	MaterialData(GLfloat spec[4], GLfloat diff[4], GLfloat amb[4], GLfloat shininess[1]);

	void setMaterial();
	
};