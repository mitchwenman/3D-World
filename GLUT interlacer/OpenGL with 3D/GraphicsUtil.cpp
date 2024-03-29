///////////////////////////////////////////////////////////////////////////////////
// Filename: GraphicsUtil.cpp
// Author: Mitch Wenman
// Date Modified: 20/05/2015
// Description: Groups together useful miscellaneous functions.
///////////////////////////////////////////////////////////////////////////////////

// ============== INCLUDES =================//
#include "GraphicsUtil.h"

// ============== FUNCTIONS =================//
glm::vec3 GraphicsUtil::vertex3ToGLMVec3(Vertex3 v)
{
	return glm::vec3(v.x, v.y, v.z);
}

Vertex3 GraphicsUtil::GLMVec3ToVertex3(glm::vec3 v)
{
	Vertex3 rv = { v.x, v.y, v.z };
	return rv;
}

double GraphicsUtil::degreesToRadians(double theta)
{
	return theta * (atan(1.0) * 4) / 180.0; 
}