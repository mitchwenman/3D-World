#pragma once

#include "GraphicsUtil.h"
#include "libs\glm\glm.hpp"
#include "WorldObject.h"

//! A class implementing the singleton pattern used to define the position and direction of the camera.
class Camera : public WorldObject
{
private:
	
	//! The eye vector.
	Vertex3 eye;

	//! The centre vector
	Vertex3 center;

	//! The up vector.
	Vertex3 up;

	//! The angle between the eye and center vectors, offset by -90 degrees i.e facing forwards is 0 degrees.
	double angle; 

	//! Creates a camera with the following values: eye(5.5, .5, 9) center(5.5, .5, 8), up(0, 1, 0). These values are the starting position for the game.
	//! Creates the "look at" matrix but does not set it until setCamera() is called.
	Camera();

public:

	//! Gets the camera singleton object.
	//! @return The singleton instance of Camera.
	static Camera* getSingleton();
	
	//! Sets the camera the position, direction and up vector of the camera.
	//! @param eyex The x coordinate of the eye vector.
	//! @param eyey The y coordinate of the eye vector.
	//! @param eyez The z coordinate of the eye vector.
	//! @param centrex The x coordinate of the centre vector.
	//! @param centrey The y coordinate of the centre vector.
	//! @param centrez The z coordinate of the centre vector.
	//! @param upx The x coordinate of the up vector.
	//! @param upy The y coordinate of the up vector.
	//! @param upz The z coordinate of the up vector.
	void lookAt(double eyex, double eyey, double eyez, double centrex, double centrey, double centrez, double upx, double upy, double upz );

	//! Multiplies the model view matrix by the current camera "look at" matrix
	//! @sideeffect Will modify the camera position/direction in the world for the next draw() call, unless the model view matrix is reset.
	void setCamera();

	//! Gets the current camera matrix
	//! @return The camera matrix.
	glm::mat4 getLookAtMatrix();

	//! Gets the eye vector
	//! @return The eye vector.
	Vertex3 getEye() { return this->eye; }

	//! The center vector
	//! @return The center vector
	Vertex3 getCentre() { return this->center; }

	//! The up vector
	//! @return The up vector
	Vertex3 getUp() { return this->up; }

	//! The angle getter
	//! @return The angle between the center and eye
	double getAngle() { return this->angle; }

	//! Sets the angle between the center and the eye vectors. Does not actually modify the two vectors.
	//! @param angle The new angle.
	void setAngle(double angle);

	void draw() {};

	//! Tests if the camera collides with any object in the game world i.e. walls or polygons. 
	//! @param otherObject The object that potentially collides with the camera i.e. the object to be tested.
	//! @returns True if the object collides with the camera, else false.
	bool collides(WorldObject *otherObject);

};