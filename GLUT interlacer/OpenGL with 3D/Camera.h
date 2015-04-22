#pragma once

#include "GraphicsUtil.h"
#include "libs\glm\glm.hpp"

class Camera
{
public:
	Vertex3 eye;
	Vertex3 center;
	Vertex3 up;

	static Camera* getSingleton();
	
	void lookAt(double eyex, double eyey, double eyez, double centrex, double centrey, double centrez, double upx, double upy, double upz );

	glm::mat4 getLookAtMatrix();

private:
	Camera();

};