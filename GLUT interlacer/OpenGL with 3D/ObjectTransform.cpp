#include "ObjectTransform.h"

void ObjectTransform::translateObject(WorldObject *object, double dx, double dy, double dz)
{
	std::vector<Transformation *> objectTransformations = object->transformations;
	Transformation *translateTrans = NULL;
	//Find first transformation that is a translate
	unsigned int i;
	for (i = 0; i < objectTransformations.size(); i++)
	{
		if (objectTransformations[i]->type == TRANSLATE)
		{
			translateTrans = objectTransformations[i];
			break;
		}
	}
	if (translateTrans == NULL)
	{
		Vertex4 values = { 0, 0, 0, 0 };
		translateTrans = new Transformation(TRANSLATE, values);
	}					
	//Add -z value to translation
	translateTrans->values.x += dx;
	translateTrans->values.y += dy;
	translateTrans->values.z += dz;
	//Add to transformation list if wasn't in there before
	if (i == objectTransformations.size())
	{
		objectTransformations.push_back(translateTrans);
	} 
	object->transformations = objectTransformations;
}