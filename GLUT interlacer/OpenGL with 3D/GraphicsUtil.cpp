#include "GraphicsUtil.h"

glm::vec3 GraphicsUtil::vertex3ToGLMVec3(Vertex3 v)
{
	return glm::vec3(v.x, v.y, v.z);
}

Vertex3 GraphicsUtil::GLMVec3ToVertex3(glm::vec3 v)
{
	Vertex3 rv = { v.x, v.y, v.z };
	return rv;
}