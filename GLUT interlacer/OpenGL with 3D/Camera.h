#pragma once

#include "GraphicsUtil.h"
#include "libs\glm\glm.hpp"

class Camera
{
private:
	Vertex3 eye;
	Vertex3 center;
	Vertex3 up;

	double angle; //Angle between center.x and eye.x

	Camera();

public:

	static Camera* getSingleton();
	
	void lookAt(double eyex, double eyey, double eyez, double centrex, double centrey, double centrez, double upx, double upy, double upz );

	//void moveEye(double eyex, double eyey, double eyez);

	//Changes the model view matrix to whatever values the camera currently has
	void setCamera();

	void moveEye(double eyex, double eyey, double eyez);

	//Getters
	glm::mat4 getLookAtMatrix();

	Vertex3 getEye() { return this->eye; }

	Vertex3 getCentre() { return this->center; }

	Vertex3 getUp() { return this->up; }

	double getAngle() { return this->angle; }

	//Setters
	void setAngle(double angle) { this->angle = angle; }

};