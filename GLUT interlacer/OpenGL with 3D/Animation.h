#pragma once

#include "Transformation.h"

class Animation : public Transformation
{
private:
	double lastUpdated;

public:
	//! The values that will be added to the base transformation values at the specified rate.
	Vertex4 animationValues;

	//! The rate (in ms) at which the object will be animated.
	double rate;

	//! Applies the animationValues to the base transformation values if the time specified by rate has passed since the last update.
	void apply();

	//! Constructor for the object.
	//! @param type The type of animation. Rotate, translate or scale.
	//! @param values The transformation values.
	//! @param rate The animation rate (in ms)
	//! @param animationValues The values that will be applied to values at the specified rate.
	Animation(TransformationType type, Vertex4 values, double rate, Vertex4 animationValues) : Transformation(type, values), 
																									animationValues(animationValues), 
																									rate(rate), lastUpdated(0) {};
};