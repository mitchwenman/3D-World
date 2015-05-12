#pragma once

#include "GraphicsUtil.h"
#include "libs\glm\glm.hpp"
#include "WorldObject.h"

class Camera : public WorldObject
{
private:
	Vertex3 eye;
	Vertex3 center;
	Vertex3 up;

	//! Angle between the eye and center vectors, offset by -90 degrees.
	double angle; 

	//! Creates a camera with the following values: eye(5.5, .5, 9) center(5.5, .5, 8), up(0, 1, 0)
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

	///Gets the current camera matrix
	///@return The camera matrix.
	glm::mat4 getLookAtMatrix();

	///Gets the eye vector
	///@return The eye vector.
	Vertex3 getEye() { return this->eye; }

	///The center vector
	///@return The center vector
	Vertex3 getCentre() { return this->center; }

	///The up vector
	///@return The up vector
	Vertex3 getUp() { return this->up; }

	///The angle getter
	///@return The angle between the center and eye
	double getAngle() { return this->angle; }

	///Sets the angle between the center and the eye vectors. Does not actually modify the two vectors.
	///@param angle The new angle.
	void setAngle(double angle);

	void draw() {};

	//! Tests if the camera collides with any object in the game world i.e. walls or polygons. 
	//! @param otherObject The object that potentially collides with the camera i.e. the object to be tested.
	//! @returns True if the object collides with the camera, else false.
	bool collides(WorldObject *otherObject);

};