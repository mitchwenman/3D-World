#pragma once

#include <vector>
#include <string>

//! A namespace for grouping together functions related to reading a Maze from file.

namespace MazeReader
{
	//! Reads a maze file at the given path and constructs
	//! a 2D vector representing it, where True represents a wall and false represents the absence of a wall.
	/*! Pseudocode
		@verbatim
		openFile()
		for (each line I)
			for (each character J)
				if (J not whitespace)
					if (J == 1)
						vector[i][j] = true
					else 
						vector[i][j] = false
		return vector
	*/
	//! @param path The path to the file.
	//! @returns A 2D vector of booleans, where true represents a wall at position i,j.
	std::vector<std::vector<bool>> readFromFile(std::string path);
};