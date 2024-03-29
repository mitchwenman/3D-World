///////////////////////////////////////////////////////////////////////////////////
// Filename: Polygon.cpp
// Author: Mitch Wenman
// Date Modified: 20/05/2015
// Description: Encapsulates an obj file that has been read in.
///////////////////////////////////////////////////////////////////////////////////

// ============== INCLUDES =================//
#include "Polygon.h"
#include "WaveFrontPolygon.h"
#include "WaveFrontPolygonDrawer.h"
#include "GraphicsSettings.h"
#include "ModelTransform.h"
#include "libs\glew.h"
#include "libs\glut.h"

// ============== FUNCTIONS =================//
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
	if (GraphicsSettings::getSingleton()->drawBoundingSphere)
		glutWireSphere(boundingSphere.radius, 16, 16);
}

PolygonWorldObject::PolygonWorldObject(WaveFrontPolygon* polygon,
						IShaderProgram* shaderProgram, 
						std::vector<Transformation*> trans) : WorldObject(shaderProgram, trans), polygon(polygon)
{
	boundingSphere = *(new TransformableBoundingSphere(*polygon));	
}

bool PolygonWorldObject::collides(WorldObject *object)
{
	this->boundingSphere.setTransform(this->transformations);
	object->boundingSphere.setTransform(object->transformations);
	BoundingSphere *thisSphere = this->boundingSphere.transform();
	BoundingSphere *otherSphere = object->boundingSphere.transform();
	bool coll = thisSphere->collides(*otherSphere);
	delete(thisSphere);
	delete(otherSphere);
	return coll;
}