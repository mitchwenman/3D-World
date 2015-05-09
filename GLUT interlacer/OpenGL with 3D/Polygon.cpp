#include "Polygon.h"
#include "WaveFrontPolygon.h"
#include "WaveFrontPolygonDrawer.h"
#include "GraphicsSettings.h"
#include "ModelTransform.h"
#include "libs\glew.h"
#include "libs\glut.h"

static float angle = 0.1;

void PolygonWorldObject::draw()
{
	for (unsigned int i = 0; i < this->transformations.size(); i++)
	{
		transformations[i]->apply();
	}
	GraphicsSettings::getSingleton()->setGLMatrices();
	if (this->shaderProgram)
		shaderProgram->useProgram();
	else
		glUseProgram(0);
	
	WaveFrontPolygonDrawer::draw(*this->polygon);
	glutWireSphere(boundingSphere.radius, 16, 16);
}

PolygonWorldObject::PolygonWorldObject(WaveFrontPolygon* polygon,
						IShaderProgram* shaderProgram, 
						std::vector<Transformation*> trans) : WorldObject(shaderProgram, trans), polygon(polygon)
{
	boundingSphere = *(new TransformableBoundingSphere(*polygon));	
}