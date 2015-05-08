#include "ObjectTransform.h"

//Returns -1 if at the back
int getTranslateInsertPosition(WorldObject *object);

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
	if (i < objectTransformations.size())
		objectTransformations[i] = translateTrans;
	else 
	{
		objectTransformations.insert(objectTransformations.begin(), translateTrans);	
	}
	
	object->transformations = objectTransformations;
}

void ObjectTransform::rotateObject(WorldObject *object, double angle, double dx, double dy, double dz)
{
	std::vector<Transformation *> objectTransformations = object->transformations;
	Transformation *rotateTrans = NULL;
	//Find first transformation that is a translate
	unsigned int i;
	for (i = 0; i < objectTransformations.size(); i++)
	{
		if (objectTransformations[i]->type == ROTATE)
		{
			rotateTrans = objectTransformations[i];
			break;
		}
	}
	if (rotateTrans == NULL)
	{
		Vertex4 values = { 0, 0, 0, 0 };
		rotateTrans = new Transformation(ROTATE, values);
	}					
	//Add -z value to translation
	rotateTrans->values.x += angle;
	rotateTrans->values.y += dx;
	rotateTrans->values.z += dy;
	rotateTrans->values.w += dz;
	//Add to transformation list if wasn't in there before
	if (i == objectTransformations.size())
	{
		objectTransformations.push_back(rotateTrans);
	} 
	object->transformations = objectTransformations;
}

void ObjectTransform::scaleObject(WorldObject *object, double sx, double sy, double sz)
{
	std::vector<Transformation *> objectTransformations = object->transformations;
	Transformation *scaleTrans = NULL;
	//Find first transformation that is a translate
	unsigned int i;
	for (i = 0; i < objectTransformations.size(); i++)
	{
		if (objectTransformations[i]->type == SCALE)
		{
			scaleTrans = objectTransformations[i];
			break;
		}
	}
	if (scaleTrans == NULL)
	{
		Vertex4 values = { 1, 1, 1, 0 };
		scaleTrans = new Transformation(SCALE, values);
	}					
	//Add -z value to translation
	scaleTrans->values.x *= sx;
	scaleTrans->values.y *= sy;
	scaleTrans->values.z *= sz;
	//Add to transformation list if wasn't in there before
	if (i < objectTransformations.size())
		objectTransformations[i] = scaleTrans;
	else 
	{
		objectTransformations.insert(objectTransformations.begin(), scaleTrans);	
	}
	
	object->transformations = objectTransformations;
}


int getTranslateInsertPosition(WorldObject *object)
{
	std::vector<Transformation *> transformations = object->transformations;
	unsigned int size = transformations.size();
	if (size == 0)
		return -1;
	unsigned int currentTranslatePosition = size;
	unsigned int currentRotatePosition = size;
	for (unsigned int i = 0; i < size; i++)
	{
		if (transformations[i]->type == TRANSLATE)
		{
			currentTranslatePosition = i;
			break;
		}	
		if (transformations[i]->type == ROTATE)
		{
			currentRotatePosition = i;
			break;
		}
	}
	//If no translate operation, add before any current rotate operation
	if (currentTranslatePosition < size)
		return currentTranslatePosition;
	else if (currentRotatePosition < size)
		return currentRotatePosition - 1;
	else if (size == 1) //must be a scale operation
		return 0;
	else
		return -1;
}