#include "Engines/GraphicEngine/TextureCharacteristicsManager.hpp"

/*!
* \brief Construct a void TextureCharacteristicsManager
*/
fme::TextureCharacteristicsManager::TextureCharacteristicsManager()
{
	//none
}

// Destructor
fme::TextureCharacteristicsManager::~TextureCharacteristicsManager()
{
	//none
}

/*!
* \brief Construct a fme::TilesCharacteristics witch each
* \brief arguments needed
* \brief search in the map if the key entered already exists
* \brief if it exists, add the fme::TilesCharacteristics
* \brief to the fme::TextureCharacteristics corresponding
* \brief if it's not, create a fme::TextureCharacteristics
* \brief with the key, the fme::TilesCharacteristics and
* \brief the fme::TileSet
* \param key the key to get it to the map
* \param all the params to create a fme::TileCharacteristics
* \param tileSetTarget the fme::TileSet associated to the 
			fme::TextureCharacteristics
*/
bool fme::TextureCharacteristicsManager::addTextureCharacteristics(
	std::string key, 
	Vector2f const& tileSize,
	std::vector <Vector2f> texturePoints,
	double timePerFrame,
	fme::TileSet* tileSetTarget)
{
	fme::TilesCharacteristics* tilesCharacteritics = new fme::TilesCharacteristics(
																		tileSize, 
																		texturePoints,
																		timePerFrame);

	m_textureCharacteristicsIndex = m_textureCharacteristics.find(key);

	if (m_textureCharacteristicsIndex != m_textureCharacteristics.end()) {
		m_textureCharacteristicsIndex->second->addTilesCharacteristics(tilesCharacteritics);
		return true;
	}
	else
	{
		m_textureCharacteristics.insert(std::pair <std::string, fme::TextureCharacteristics*>(
			key,
			new fme::TextureCharacteristics(
					std::vector <TilesCharacteristics*>(1, tilesCharacteritics),
					tileSetTarget)));

		return false;
	}
}

bool fme::TextureCharacteristicsManager::addTextureCharacteristics(
	std::string key,
	Vector2f const& tileSize,
	Vector2f oneTexturePoint,
	fme::TileSet* tileSetTarget)
{
	std::vector <Vector2f> texturePoints;
	texturePoints.push_back(oneTexturePoint);
	return addTextureCharacteristics(key, tileSize, texturePoints, -1, tileSetTarget);
}

// Getter
fme::TextureCharacteristics* fme::TextureCharacteristicsManager::getTextureCharacteristics(std::string key)
{
	return m_textureCharacteristics[key];
}