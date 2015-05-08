#pragma once

#include "WaveFrontPolygon.h"
#include "TangentWaveFrontPolygon.h"

//! A namespace for grouping together functions for drawing polygons.
namespace WaveFrontPolygonDrawer
{
	//! Draws a polygon using glDrawElements, passing the available data via gl*Pointer calls.
	//! @param polygon The polygon to be drawn.
	void draw(WaveFrontPolygon polygon);

	//! Draws a polygon. This method is exactly the same as draw(WaveFrontPolygon polygon), except
	//! this method also passes the polygon's surface tangents to openGL via a glColour pointer.
	//! @param polygon The polygon to be draw.
	void drawNormalMapPolygon(TangentWaveFrontPolygon polygon);
}