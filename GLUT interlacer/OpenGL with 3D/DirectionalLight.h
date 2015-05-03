#pragma once

#include "GraphicsUtil.h"

class DirectionalLight
{
private:
	///Private constructor for the singleton pattern.
	///
	DirectionalLight() {};

	Vertex4 direction;
	Vertex4 ambient,
			diffuse;

public:
	///Returns the singleton light object
	///@return The singleton Directional Light object.
	static DirectionalLight* getSingleton();

	///
	///Calls the openGL lightfv functions with the current matrix.
	void setLight();
	
	///Sets the light values, but does not make openGL calls.
	///@param direction The direction of the light.
	///@param ambient The ambient colour of the light.
	///@param diffuse The diffuse colour of the light.
	void setLight(Vertex4 direction, Vertex4 ambient, Vertex4 diffuse);

	///Gets the current direction vector of the light.
	///@return The direction vector of the light.
	Vertex4 getDirection() { return direction; }
};