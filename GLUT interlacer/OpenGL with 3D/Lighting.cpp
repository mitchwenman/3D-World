#include "Lighting.h"



void Lighting::setupDirectionalLight(Vertex4 direction, Vertex4 diffuse, Vertex4 ambient)
{
	GLfloat light_direction[] = { (float)direction.x, (float)direction.y, (float)direction.z, (float)direction.w };
	//w should be equal to zero but is left to caller

	GLfloat light_defuse[] = { (float)diffuse.x, (float)diffuse.y, (float)diffuse.z, (float)diffuse.w }; //rgba w = a
	GLfloat light_ambient[] = { (float)ambient.x, (float)ambient.y, (float)ambient.z, (float)ambient.w };

	//Pass to openGL
	glLightfv(GL_LIGHT0, GL_POSITION, light_direction);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_defuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0);

}

void Lighting::setupPointLight(Vertex4 position, Vertex4 diffuse, Vertex4 ambient)
{

	GLfloat light_position[] = { (float)position.x, (float)position.y, (float)position.z, (float)position.w };
	//w should be 1 but is left to caller

	GLfloat light_defuse[] = { (float)diffuse.x, (float)diffuse.y, (float)diffuse.z, (float)diffuse.w }; //rgba w = a
	GLfloat light_ambient[] = { (float)ambient.x, (float)ambient.y, (float)ambient.z, (float)ambient.w };
	
	//Pass params
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_defuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);	
	glLightf(GL_LIGHT0,	GL_SPOT_CUTOFF,	180.0f); //disable spot light (180 deg)
}

void Lighting::setupSpotLight(Vertex4 position, Vertex4 diffuse, Vertex4 ambient, Vertex3 direction, float cutoff)
{
	GLfloat light_position[] = { (float)position.x, (float)position.y, (float)position.z, (float)position.w };
	//w should be 1 but is left to caller

	GLfloat light_defuse[] = { (float)diffuse.x, (float)diffuse.y, (float)diffuse.z, (float)diffuse.w }; //rgba w = a
	GLfloat light_ambient[] = { (float)ambient.x, (float)ambient.y, (float)ambient.z, (float)ambient.w };

	GLfloat spotlight_dir[] = { (float)direction.x, (float)direction.y, (float)direction.z };
	GLfloat spotlight_cutoff = cutoff;

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_defuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotlight_dir);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotlight_cutoff);
}