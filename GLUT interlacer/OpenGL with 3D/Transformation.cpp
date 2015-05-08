#include "Transformation.h"

#include "ModelTransform.h"

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