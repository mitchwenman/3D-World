#include "MaterialData.h"

#include <string.h>

MaterialData::MaterialData(GLfloat spec[4], GLfloat diff[4], GLfloat amb[4], GLfloat shininess[1])
{
	memcpy(ambientColour, amb, sizeof(GLfloat) * 4);
	memcpy(diffuseColour, diff, sizeof(GLfloat) * 4);
	memcpy(specularColour, spec, sizeof(GLfloat) * 4);
	memcpy(this->shininess, shininess, sizeof(shininess));
}


void MaterialData::setMaterial()
{
	glMaterialfv(GL_FRONT, GL_SPECULAR, this->specularColour);
	glMaterialfv(GL_FRONT, GL_SHININESS, this->shininess);

	glMaterialfv(GL_FRONT_AND_BACK,	GL_AMBIENT,	this->ambientColour);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, this->diffuseColour);
}