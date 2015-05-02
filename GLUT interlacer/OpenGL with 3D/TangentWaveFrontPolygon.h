#pragma once

#include "WaveFrontPolygon.h"

class TangentWaveFrontPolygon : public WaveFrontPolygon
{
public:
	std::vector<float> tangents;

	TangentWaveFrontPolygon(std::string objFile);
};