#include "Engines/GraphicEngine/TilesCharacteristics.hpp"

fme::TilesCharacteristics::TilesCharacteristics(
	fme::Vector2f const& newtileSize,
	std::vector <fme::Vector2f> newTexturePoints,
	double newTimePerFrame)
{
	m_tileSize = newtileSize;
	m_texturePoints = newTexturePoints;
	m_timePerFrame = newTimePerFrame;
}

fme::TilesCharacteristics::TilesCharacteristics(
	fme::Vector2f const& tileSize,
	fme::Vector2f const& oneTexturePoint)
	:TilesCharacteristics(tileSize, std::vector <fme::Vector2f> (1, oneTexturePoint), 0)
{
	// void
}

fme::TilesCharacteristics::~TilesCharacteristics()
{
	m_texturePoints.clear();
}

fme::Vector2f const& fme::TilesCharacteristics::getTileSize()
{
	return m_tileSize;
}

fme::Vector2f const& fme::TilesCharacteristics::getTexturePoints(unsigned int index)
{
	return m_texturePoints[index];
}

double fme::TilesCharacteristics::getTimePerFrame()
{
	return m_timePerFrame;
}

unsigned int fme::TilesCharacteristics::getArraySize()
{
	return m_texturePoints.size();
}