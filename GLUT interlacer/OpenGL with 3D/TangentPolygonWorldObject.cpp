#include "TangentPolygonWorldObject.h"

#include "GraphicsSettings.h"
#include "WaveFrontPolygonDrawer.h"
#include "ModelTransform.h"

static float angle = 0.1;

void TangentPolygonWorldObject::draw()
{
	for (unsigned int i = 0; i < this->transformations.size(); i++)
	{
		transformations[i]->apply();
	}
	ModelTransform::rotate(angle += 0.05, 1, 1, 1);
	GraphicsSettings::getSingleton()->setGLMatrices();
	if (this->shaderProgram)
		shaderProgram->useProgram();
	else
		glUseProgram(0);
	
	WaveFrontPolygonDrawer::drawNormalMapPolygon(*this->polygon);
}