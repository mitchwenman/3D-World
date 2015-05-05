#pragma once

#include "WaveFrontPolygon.h"

//! An extension of the WaveFrontPolygon.
/*!
	This class provides the ability to calculate tangent vectors
	from the object's texture coordinates. These will be used later
	by the normal map shader program to transform the normals from the 
	normal map into world space so lighting calculations can be performed.
*/
class TangentWaveFrontPolygon : public WaveFrontPolygon
{
public:
	//! The ungrouped tangents calculated from the objects texture coordinates.
	std::vector<float> tangents;

	//! Constructor for the object. Calls the subclasses constructor to load the object from file. Calculates the tangent vectors.
	//! @param objFile The obj file that describes the object.
	TangentWaveFrontPolygon(std::string objFile);
};