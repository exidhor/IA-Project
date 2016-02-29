#include "Engines/GraphicEngine/TextureCharacteristics.hpp"

//Constructor
fme::TextureCharacteristics::TextureCharacteristics(
	std::vector <fme::TilesCharacteristics*> targetTilesCharacteristics,
	fme::TileSet* targetTileSet)
{
	arrayOfTileCharacteristic = targetTilesCharacteristics;
	tileSet = targetTileSet;
}

fme::TextureCharacteristics::TextureCharacteristics(
	TilesCharacteristics* tileCharacteristics,
	TileSet* tileSet)
	:TextureCharacteristics(
		std::vector <fme::TilesCharacteristics*> (1, tileCharacteristics),
		tileSet)
{
	// void
}

//Desctructor
fme::TextureCharacteristics::~TextureCharacteristics()
{
	arrayOfTileCharacteristic.clear();
}

//Add an TilesCharacteristics at the vector
void fme::TextureCharacteristics::addTilesCharacteristics(fme::TilesCharacteristics* newArray)
{
	arrayOfTileCharacteristic.push_back(newArray);
}

//Return the TileSet
fme::TileSet* fme::TextureCharacteristics::getTileSet()  const
{
	return tileSet;
}

//Return the TileSize of an ArrayOFTileCharacteristic
fme::Vector2f const& fme::TextureCharacteristics::getTileSize(
	unsigned int indexTileCharac)  const
{
	return arrayOfTileCharacteristic[indexTileCharac]->getTileSize();
}

fme::Vector2f const& fme::TextureCharacteristics::getTexturePoints(unsigned int indexCulumn,
	unsigned int indexLine)  const
{
	return arrayOfTileCharacteristic[indexLine]->getTexturePoints(indexCulumn);
}

//Return the ArraySize of an ArrayOFTileCharacteristic
unsigned int fme::TextureCharacteristics::getLineSizeOf(
	unsigned int indexTileCharac) const
{
	return arrayOfTileCharacteristic[indexTileCharac]->getArraySize();
}

unsigned int fme::TextureCharacteristics::getCulumnSize() const
{
	return arrayOfTileCharacteristic.size();
}

//Return the TimePerFrame of an ArrayOFTileCharacteristic
double fme::TextureCharacteristics::getTimePerFrame(
	unsigned int indexTileCharac) const
{
	return arrayOfTileCharacteristic[indexTileCharac]->getTimePerFrame();
}