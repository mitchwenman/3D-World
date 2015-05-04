#pragma once

//! Groups together functions for modifying the model view matrix.
namespace ModelTransform
{
	//!Translates the model view matrix by the given values.
	//! @param x The x translation.
	//! @param y The y translation.
	//! @param z The z translation.
	void translate(double x, double y, double z);

	//! Rotates the model view matrix by the given values.
	//! @param angle The angle of the rotation.
	//! @param x The amount of rotation applied to the x axis.
	//! @param y The amount of rotation applied to the y axis.
	//! @param z The amount of rotation applied to the z axis.
	void rotate(float angle, double x, double y, double z);

	//! Scales the model view matrix by the given values.
	//! @param x The x axis scaling factor.
	//! @param y The y axis scaling factor.
	//! @param z The z axis scaling factor.
	void scale(double x, double y, double z);
};