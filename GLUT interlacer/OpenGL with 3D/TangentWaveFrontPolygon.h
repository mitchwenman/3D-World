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
	/*!
		Pseudocode:
		@verbatim
			verts = groupVertices()
			texts = groupTextureCoords()
			for (each triangle)
				edge1 = getEdge1(triangle)
				edge2 = getEdge2(triangle)
				getUV'1()
				getUV'2()
				uvMatrix = mat2x2(UV'1, UV'2)
				inverseUV = inverse(uvMatrix)
				edgeMatrix = mat2x3(edge1, edge2)
				tbMatrix = inverseUV * edgeMatrix
				tangent = tbMatrix[0]
				for (each vertexIndex(triangle))
					tangents[vertexIndex] += tangent
			for (each tangent)
				normalise(tangent)
		@endverbatim
	*/
	//! @param objFile The obj file that describes the object.
	TangentWaveFrontPolygon(std::string objFile);
};