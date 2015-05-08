#include "ObjectTransform.h"

#include "World.h"

//Returns -1 if at the back
int getTranslateInsertPosition(WorldObject *object);

bool collidesWithWorld(WorldObject* object);

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
		i = 0;
	}
	object->transformations = objectTransformations;
	if (collidesWithWorld(object))
	{
		//Reset
		Transformation *newTrans = objectTransformations[i];
		newTrans->values.x -= dx;
		newTrans->values.y -= dy;
		newTrans->values.z -= dz;
	}
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
	if (collidesWithWorld(object))
	{
		//Reset
		Transformation *newRotate = objectTransformations[i];
		newRotate->values.x -= angle;
		newRotate->values.y -= dx;
		newRotate->values.z -= dy;
		newRotate->values.w -= dz;
	}
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
		objectTransformations.push_back(scaleTrans);	
	}
	
	object->transformations = objectTransformations;
}

//Returns an
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
		return 1;
	else
		return -1;
}

bool collidesWithWorld(WorldObject* object)
{
	World *world = World::getInstance();
	std::vector<WorldObject*> objects = world->objects;

	unsigned int numCollisions = 0;
	for (std::vector<WorldObject*>::iterator it = objects.begin();
		it != objects.end(); it++)
	{
		if (object->collides((*it)))
		{
			numCollisions++;
			if (numCollisions == 2) //The object will collide with itself
				break;
		}
	}
	return numCollisions == 2;
}