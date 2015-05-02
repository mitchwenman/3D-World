#pragma once

#include "WaveFrontPolygon.h"

class TangentWaveFrontPolygon : public WaveFrontPolygon
{
public:
	std::vector<double> tangents;

	TangentWaveFrontPolygon(std::string objFile);
};