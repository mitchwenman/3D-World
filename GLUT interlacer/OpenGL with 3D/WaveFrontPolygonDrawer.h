#pragma once

#include "WaveFrontPolygon.h"
#include "TangentWaveFrontPolygon.h"

namespace WaveFrontPolygonDrawer
{
	void draw(WaveFrontPolygon polygon);

	void drawNormalMapPolygon(TangentWaveFrontPolygon polygon);
}