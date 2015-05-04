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
	/*
	 * Default private constructor for singleton pattern
	 */
	Camera();

public:

	///Gets the camera singleton object
	///@return The singleton instance of Camera.
	static Camera* getSingleton();
	
	///Sets the camera the position, direction and up vector of the camera.
	///@param eyex, eyey, eyez The location of the camera
	///@param centrex, centrey, centrez The point at which the camera will face.
	///@param upx, upy, upz The up vector.
	void lookAt(double eyex, double eyey, double eyez, double centrex, double centrey, double centrez, double upx, double upy, double upz );

	///Multiplies the model view matrix by the current camera values
	void setCamera();

	void moveEye(double eyex, double eyey, double eyez);

	///Gets the current camera matrix
	///@return The camera matrix.
	glm::mat4 getLookAtMatrix();

	///Gets the eye vector
	///@return the eye vector.
	Vertex3 getEye() { return this->eye; }

	///The center vector
	///@return the center vector
	Vertex3 getCentre() { return this->center; }

	///The up vector
	///@return the up vector
	Vertex3 getUp() { return this->up; }

	///The angle getter
	///@return the angle between the center and eye
	double getAngle() { return this->angle; }

	///Sets the angle
	///@param angle The new angle.
	void setAngle(double angle);

};