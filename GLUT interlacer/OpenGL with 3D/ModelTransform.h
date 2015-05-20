#pragma once

//! Groups together functions for modifying the model view matrix.
namespace ModelTransform
{
	//!Translates the model view matrix by the given values.
	//! @param x The x translation.
	//! @param y The y translation.
	//! @param z The z translation.
	//! @sideeffect The model view matrix is translated by the given values.
	void translate(double x, double y, double z);

	//! Rotates the model view matrix by the given angle around a vector given by x, y, z.
	//! @param angle The angle of the rotation.
	//! @param x The x component of the vector.
	//! @param y The y component of the vector.
	//! @param z The z component of the vectors.
	//! @sideeffect The model view matrix is rotated by the given values.
	void rotate(float angle, double x, double y, double z);

	//! Scales the model view matrix by the given values.
	//! @param x The x axis scaling factor.
	//! @param y The y axis scaling factor.
	//! @param z The z axis scaling factor.
	//! @sideeffect The model view matrix is scaled by the given values.
	void scale(double x, double y, double z);
};