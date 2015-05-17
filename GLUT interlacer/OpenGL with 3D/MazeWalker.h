#pragma once

#include "Polygon.h"
#include "IShaderProgram.h"
#include "WaveFrontPolygon.h"
#include "Maze.h"
#include "libs\glm\glm.hpp"
#include "Animation.h"

#include <vector>
#include <map>
#include <utility>

//! A class that represents an object moving around a maze.
/*!
	The class inserts a random object, defined by given polygon, into the maze.
	The object is inserted into the world and enters into the draw loop. The object
	simply moves from it's current tile to the the adjacent tiles randomly while avoiding
	other objects in the world. Collision detect is not performed on the walls, as the objects
	movement algorithm avoids collision with walls.
*/
class MazeWalker : public PolygonWorldObject
{
private:

	//! A reference to the maze that the object will move around in.
	Maze *maze;

	//! A 2D vector of possible positions for the walker. This is simply the inverse
	//! of the wall positions described by the maze.
	std::map<std::pair<int, int>, void*> positions;

	//! The current position in world space of the object.
	glm::vec3 position;

	//! The current target of the walker i.e. the tile it is moving towards.
	glm::vec3 target;

	//! A reference to the animation that defines the walker's movement through the maze.
	Animation* movingAnimation;

	//! Given the walker's current position, gets a new random target.
	/*!
		Pseudocode:
		@verbatim
			pos = getPositionInMaze()
			if (pos.above() isValid)
				validPositions.add(above)
			if (pos.below() isValid)
				validPosition.add(below)
			if (pos.left() isValid)
				validPosition.add(left)
			if (pos.right() isValid)
				validPosition.add(right)
			validPosition.add(pos) // Current position for chance of staying still
			target = getRandom(validPosition)
			return targetB
		@endverbatim
	*/
	//! @param position The current position of the walker.
	//! @return A random target, either above, below, left or right of the current position.
	glm::vec3 getTargetForPosition(glm::vec3 position);

	//! Given the walker's current position and target position, creates
	//! an animation transformation that will gradually move the object
	//! towards the target. Caller is responsible for deletion of the new animation.
	/*!
		Pseudocode:
		@verbatim
			animation = new Animation()
			animation.values = position
			animation.animationValues = target - position / 50
			animation.rate = 25
			return animation
		@endverbatim
	*/
	//! @param position The current position of the walker.
	//! @param target The current target of the walker.
	//! @return An animation that will move the walker towards the target.
	Animation* createAnimation(glm::vec3 position, glm::vec3 target);

	//! Checks whether the object is at the position. 
	//! Note: Due to precision, the object will never be exactly at the position,
	//! so this returns true if the object is close to the target.
	/*!
		Pseudocode:
		@verbatim
			return abs(target.x - position.x) < 0.01 &&
					abs(target.z - position.z) < 0.01)
		@endverbatim
	*/
	//! @param position The current position of the walker.
	//! @param target The current target of the walker.
	//! @return True if the position is very close or at the target, else false.
	bool isAtTarget(glm::vec3 position, glm::vec3 target);

public:
	//! Draws the walker at its current position. 
	/*!
		 First checks if the object is at its target. If so, a new target is created. The current movingAnimation
		 is then applied and any collisions are detected. A new target is selected
		 if collisions are detected. The object is then drawn.
		 Pseudocode:
		 @verbatim
			if (isAtTarget)
				target = getRandomTarget(position)
				movingAnimation = createAnimation(position, target)
			movingAnimation.apply()
			if (this.collidesWithOtherObjects())
				target = getRandomTarget(position)
				movingAnimation = createAnimation(position, target)
			setCamera()
			useProgram(shaderProgram)
			draw(polygon)
		 @endverbatim
	*/
	void draw();

	//! Creates a maze walker given a polygon to represent it, a shader program and the maze it will traverse.
	/*!
		A random entry position into the maze is selected while checking for collisions, then
		a random target position adjacent to it.
		Pseudocode:
		@verbatim
			World.insert(this)
			positions = getListOfPositions(maze)
			do
				this.position = getRandomPosition(positions)
			while (this.collidesWithOtherObjects())
			target = getRandomTarget(position)
			movingAnimation = createAnimation(position, target)
		@endverbatim
	*/
	//! @param polygon The polygon that will be drawn at the walker's position
	//! @param program The shader program that will be used to draw the object.
	//! @param maze The maze that the walker will traverse.
	MazeWalker(WaveFrontPolygon *polygon, IShaderProgram *program, Maze* maze);
};