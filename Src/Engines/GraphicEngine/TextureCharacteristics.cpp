#include "Engines/GraphicEngine/TextureCharacteristics.hpp"

//Constructor
fme::TextureCharacteristics::TextureCharacteristics(
		std::vector <fme::TilesCharacteristics*> targetTilesCharacteristics,
		fme::TileSet* targetTileSet)
{
	m_arrayOfTileCharacteristic = targetTilesCharacteristics;
	m_tileSet = targetTileSet;
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

fme::TextureCharacteristics::TextureCharacteristics(
		TileSet* tileSet,
		float width,
		float height)
{
	m_tileSet = tileSet;
	m_arrayOfTileCharacteristic.push_back(new TilesCharacteristics(Vector2f(width, height),
																	std::vector <Vector2f> (), 0));
}

//Desctructor
fme::TextureCharacteristics::~TextureCharacteristics()
{
	m_arrayOfTileCharacteristic.clear();
}

//Add an TilesCharacteristics at the vector
void fme::TextureCharacteristics::addTilesCharacteristics(fme::TilesCharacteristics* newArray)
{
	m_arrayOfTileCharacteristic.push_back(newArray);
}

//Return the TileSet
fme::TileSet* fme::TextureCharacteristics::getTileSet()  const
{
	return m_tileSet;
}

//Return the TileSize of an ArrayOFTileCharacteristic
Vector2f const& fme::TextureCharacteristics::getTileSize(
	unsigned int indexTileCharac)  const
{
	return m_arrayOfTileCharacteristic[indexTileCharac]->getTileSize();
}

Vector2f const& fme::TextureCharacteristics::getTexturePoints(
	unsigned int indexCulumn,
	unsigned int indexLine)  const
{
	return m_arrayOfTileCharacteristic[indexLine]->getTexturePoints(indexCulumn);
}

//Return the ArraySize of an ArrayOFTileCharacteristic
unsigned int fme::TextureCharacteristics::getLineSizeOf(
	unsigned int indexTileCharac) const
{
	return m_arrayOfTileCharacteristic[indexTileCharac]->getArraySize();
}

unsigned int fme::TextureCharacteristics::getCulumnSize() const
{
	return m_arrayOfTileCharacteristic.size();
}

//Return the TimePerFrame of an ArrayOFTileCharacteristic
double fme::TextureCharacteristics::getTimePerFrame(
	unsigned int indexTileCharac) const
{
	return m_arrayOfTileCharacteristic[indexTileCharac]->getTimePerFrame();
}