#pragma once

#include "libs\glew.h"
#include "libs\glut.h"

//! A class representing a material.
/*!
	Groups data describing the colour of the material.
	Also stores the material's shininess.
*/
class MaterialData
{
public:
	//! The specular colours of the material
	GLfloat specularColour[4];

	//! The diffuse colour of the material.
	GLfloat diffuseColour[4];

	//! The ambient colour of the material.
	GLfloat ambientColour[4];

	//! The shininess of the material.
	GLfloat shininess[1];

	//! Constructor for the class. Sets the provided values.
	//! @param spec THe specular colour of the material.
	//! @param diff The diffuse colour of the material.
	//! @param amb The ambient colour of the material.
	//! @param shininess The shininess of the material. Should be a value between 0 and 128.
	MaterialData(GLfloat spec[4], GLfloat diff[4], GLfloat amb[4], GLfloat shininess[1]);

	//! Passes the material data to open GL. Should be called prior to rendering the object.
	void setMaterial();
	
};