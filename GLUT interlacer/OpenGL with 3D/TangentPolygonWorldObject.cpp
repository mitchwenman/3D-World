///////////////////////////////////////////////////////////////////////////////////
// Filename: TangentPolygonWorldObject.cpp
// Author: Mitch Wenman
// Date Modified: 20/05/2015
// Description: Encapsulates a pointer to a polygon with tangents calculated.
///////////////////////////////////////////////////////////////////////////////////

// ============== INCLUDES =================//
#include "TangentPolygonWorldObject.h"
#include "GraphicsSettings.h"
#include "WaveFrontPolygonDrawer.h"
#include "ModelTransform.h"

// ============== FUNCTIONS =================//
void TangentPolygonWorldObject::draw()
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
	
	WaveFrontPolygonDrawer::drawNormalMapPolygon(*this->polygon);
	if (GraphicsSettings::getSingleton()->drawBoundingSphere)
		glutWireSphere(boundingSphere.radius, 16, 16);
}

TangentPolygonWorldObject::TangentPolygonWorldObject(TangentWaveFrontPolygon* polygon,
						IShaderProgram* shaderProgram, 
						std::vector<Transformation*> trans) : WorldObject(shaderProgram, trans), polygon(polygon)
{ 
	boundingSphere = *(new TransformableBoundingSphere(*polygon));
}

bool TangentPolygonWorldObject::collides(WorldObject *object)
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