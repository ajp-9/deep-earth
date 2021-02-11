#pragma once

#include "../../../../Engine/Util/TypeDefs.hpp"

class Light
{
public:

	Light() : m_Data(0) {}

	byte getArtificialLight();
	byte getSunLight();

	void setArtificialLight(byte light_level);
	void setSunLight(byte light_level);

private:

	byte m_Data;
};

/*
	data:

	0xF0 = sunlight
	0x0F = artificial light

*/