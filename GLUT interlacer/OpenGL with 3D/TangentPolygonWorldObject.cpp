#include "TangentPolygonWorldObject.h"

#include "GraphicsSettings.h"
#include "WaveFrontPolygonDrawer.h"
#include "ModelTransform.h"

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
}