#pragma once

#include "libs\glew.h"
#include "libs\glut.h"
#include "libs\glm\glm.hpp"


typedef struct { double x; double y; double z; double w; } Vertex4;

typedef struct { double x; double y; double z; } Vertex3;

typedef struct { double x; double y; } Vertex2;

namespace GraphicsUtil
{
	glm::vec3 vertex3ToGLMVec3(Vertex3 v);

	Vertex3 GLMVec3ToVertex3(glm::vec3);
}


