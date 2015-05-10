#pragma once


#include <vector>

#include "WaveFrontPolygon.h"
#include "HeightMap.h"
#include "MaterialData.h"
#include "Transformation.h"
#include "WorldObject.h"
#include "IShaderProgram.h"
#include "Maze.h"
#include "HeightMapWorldObject.h"

//! A class to define the scene/world.
/*!
	This class is responsible for managing the state of the world. In essence,
	the class simply invokes each object's own draw method in the draw loop (as well as
	resetting the model view matrix when required. The class also implements the user interface
	for selecting polygons, by changing the polygon's shader to indicate that it is currently selected.
*/
class World
{

private:
	//! The index of the currently selected object.
	int selectedObject;

	//! A pointer to the shader that will be used on the currently selected polygon.
	IShaderProgram* hightlightShader;

	//! Holds the pointer to the selected polygon's original shader, since it has been
	//! temporarily replaced by highlightShader
	IShaderProgram* currentSelectedPolygonShader;

	//! Private constructor for the singleton pattern. Creates the shader program held by highlightShader.
	World();
		

public:
	//! All standalone objects in the world.
	std::vector<WorldObject *> objects;

	//! The world's maze
	Maze *maze;

	//! The world's terrain
	HeightMapWorldObject* heightMap;

	//! Gets the singleton instance of the class.
	//! @return The singleton instance of the class.
	static World* getInstance();

	//! Sets the camera and invokes the draw method of each object in objects.
	void draw();

	//! Inserts an object into objects. This object will be drawn in turn on the next invocation of draw().
	void insertObject(WorldObject *object);
	
	//! Increments currently selected object. Replaces the previously selected object's shader program,
	//! increments selectedObject and takes a copy of the selected object's shader program before replacing it with hightlightShader.
	//! If the currently selected object is at the back of the object list, then selected object is set to -1.
	void toggleSelectedObject();

	//! Gets the index of the currently selected object.
	//! @return The index of the curently selected object.
	int getSelectedObjectIndex() { return selectedObject; }


};