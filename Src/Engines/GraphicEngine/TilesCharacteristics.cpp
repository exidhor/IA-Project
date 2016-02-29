#include "Engines/GraphicEngine/TilesCharacteristics.hpp"

fme::TilesCharacteristics::TilesCharacteristics(
	fme::Vector2f const& newtileSize,
	std::vector <fme::Vector2f> newTexturePoints,
	double newTimePerFrame)
{
	tileSize = newtileSize;
	tileSize = newtileSize;
	texturePoints = newTexturePoints;
	timePerFrame = newTimePerFrame;
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
	texturePoints.clear();
}

fme::Vector2f const& fme::TilesCharacteristics::getTileSize()
{
	return tileSize;
}

fme::Vector2f const& fme::TilesCharacteristics::getTexturePoints(unsigned int index)
{
	return texturePoints[index];
}

double fme::TilesCharacteristics::getTimePerFrame()
{
	return timePerFrame;
}

unsigned int fme::TilesCharacteristics::getArraySize()
{
	return texturePoints.size();
}