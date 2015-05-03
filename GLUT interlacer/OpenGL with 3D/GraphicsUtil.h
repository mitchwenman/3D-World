#pragma once

#include "libs\glew.h"
#include "libs\glut.h"
#include "libs\glm\glm.hpp"

//! Describes a 4D vertex. 
typedef struct { double x; double y; double z; double w; } Vertex4;

//! Describes a 3D vertex
typedef struct { double x; double y; double z; } Vertex3;

//! Describes a 2D vertex
typedef struct { double x; double y; } Vertex2;

namespace GraphicsUtil
{
	//! Converts a Vertex3 to glm vec3
	//! @param v The vertex to be converted
	//! @return A vec3 representation of the Vertex
	glm::vec3 vertex3ToGLMVec3(Vertex3 v);

	//! Converts a glm vec3 to a Vertex3
	//! @param v The glm vec3 to be converted.
	//! @return A Vertex3 equivalent of the vec3
	Vertex3 GLMVec3ToVertex3(glm::vec3 v);
}


