///////////////////////////////////////////////////////////////////////////////////
// Filename: Transformation.cpp
// Author: Mitch Wenman
// Date Modified: 20/05/2015
// Description: Encapsulates a model view transformation.
///////////////////////////////////////////////////////////////////////////////////

// ============== INCLUDES =================//
#include "Transformation.h"
#include "ModelTransform.h"

// ============== FUNCTIONS =================//
void Transformation::apply()
{
	switch (type)
	{
	case TRANSLATE:
	{
		ModelTransform::translate(values.x, values.y, values.z);
		break;
	}
	case ROTATE:
	{
		ModelTransform::rotate(values.x, values.y, values.z, values.w);
		break;
	}
	case SCALE:
	{
		ModelTransform::scale(values.x, values.y, values.z);
		break;
	}
	}
}