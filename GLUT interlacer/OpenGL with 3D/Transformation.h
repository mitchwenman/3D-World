#pragma once

#include "GraphicsUtil.h"

//! The type of transformation. Rotate, translate or scale.
typedef enum { TRANSLATE, ROTATE, SCALE } TransformationType;

//! Encapsulates a model view transformation.
class Transformation
{
public:
	//! The type of transformation. Translate, rotate or scale.
	TransformationType type;

	//! The values for the transformation. dx, dy, dz for scaling and translating. Angle, dx, dy, dz for rotation transformations.
	Vertex4 values;

	//! Constructor for the object. Sets the given values.
	//! @param t The type of transformation.
	//! @param v The values for the transformation.
	Transformation(TransformationType t, Vertex4 v) : type(t), values(v) {};

	//! Applies the transformation by multiplying the current model view matrix by the generated transformation matrix.
	/*!
		Pseudocode:
		@verbatim
			if (type == TRANSLATE)
				ModelTransform.translate(values.x, values.y, values.z)
			else if (type == ROTATE)
				ModelTransform.rotate(values.x, values.y, values.z, values.w)
			else if (type == SCALE)
				ModelTransform.scale(values.x, values.y, values.z)
		@endverbatim
	*/
	virtual void apply();
};