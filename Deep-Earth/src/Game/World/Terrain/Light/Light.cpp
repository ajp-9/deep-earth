#include "Light.hpp"

byte Light::getArtificialLight()
{
	return (m_Data & 0xF0) >> 4;
}

byte Light::getSunLight()
{
	return (m_Data & 0x0F) >> 0;
}

void Light::setArtificialLight(byte light_level)
{
	m_Data = (light_level << 4) | m_Data;
}

void Light::setSunLight(byte light_level)
{
	m_Data = light_level | m_Data;
}