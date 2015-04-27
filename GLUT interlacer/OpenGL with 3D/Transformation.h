#pragma once

#include "GraphicsUtil.h"

typedef enum { TRANSLATE, ROTATE, SCALE } TransformationType;

class Transformation
{
public:
	TransformationType type;

	//Translate/Scale: { x, y, z }
	//Rotate: { angle, x, y z }
	Vertex4 values;

	Transformation(TransformationType t, Vertex4 v) : type(t), values(v) {};

	void apply();
};