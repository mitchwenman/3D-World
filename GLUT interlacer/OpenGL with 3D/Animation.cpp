///////////////////////////////////////////////////////////////////////////////////
// Filename: Animation.cpp
// Author: Mitch Wenman
// Date Modified: 20/05/2015
// Description: Class for encapsulating a model view transformation.
///////////////////////////////////////////////////////////////////////////////////

// ============== INCLUDES =================//
#include "Animation.h"

#include <Windows.h>

// ============== FUNCTIONS =================//
void Animation::apply()
{
	double currentTime = GetTickCount64();
	if (currentTime - this->lastUpdated > rate)
	{
		if (type == ROTATE)
		{
			this->values.x += this->animationValues.x; //Increase angle
			this->values.y = this->animationValues.y;
			this->values.z = this->animationValues.z;
			this->values.w = this->animationValues.w;
		} else if (type == TRANSLATE)
		{
			this->values.x += this->animationValues.x; 
			this->values.y += this->animationValues.y;
			this->values.z += this->animationValues.z;
		} else if (type == SCALE)
		{
			this->values.x += this->animationValues.x; 
			this->values.y += this->animationValues.y;
			this->values.z += this->animationValues.z;
		}
		this->lastUpdated = currentTime;
	}
	Transformation::apply();
}