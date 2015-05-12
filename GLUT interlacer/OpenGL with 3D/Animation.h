#pragma once

#include "Transformation.h"

//! Extends the standard transformation class by allowing transformation values to change over time.
/*!
	The Animation class extends the standard transformation class by allowing a stored transformation to change
	over time. The transformation is changed by the set of values: animationValues at a rate specified by rate.
	This means the transformation values change independently of the number of times apply() is called.
*/
class Animation : public Transformation
{
private:
	//! The time (in ms) that the transformation values were last updated.
	double lastUpdated;

public:
	//! The values that will be added to the base transformation values at the specified rate.
	Vertex4 animationValues;

	//! The rate (in ms) at which the object will be animated.
	double rate;

	//! Applies the animationValues to the base transformation values if the time specified by rate has passed since the last update.
	/*! Pseudocode:
		@verbatim
			interval = GetCurrentTime() - lastUpdated
			if (interval > rate)
				this.values += animationValues
		@endvertbatim
	*/
	void apply();

	//! Constructor for the object.
	//! @param type The type of animation. Rotate, translate or scale.
	//! @param values The transformation values.
	//! @param rate The animation rate (in ms)
	//! @param animationValues The values that will be applied to the transformation values at the specified rate.
	Animation(TransformationType type, Vertex4 values, double rate, Vertex4 animationValues) : Transformation(type, values), 
																									animationValues(animationValues), 
																									rate(rate), lastUpdated(0) {};
};