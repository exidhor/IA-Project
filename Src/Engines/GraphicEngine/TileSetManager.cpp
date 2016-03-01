#include "Engines/GraphicEngine/TileSetManager.hpp"

//Constructor
fme::TileSetManager::TileSetManager()
{
	//none
}

//Destructor
fme::TileSetManager::~TileSetManager()
{
	for (std::map<std::string, fme::TileSet*>::iterator tileSet = m_tileSetMap.begin();
		tileSet != m_tileSetMap.end(); ++tileSet)
	{
		delete tileSet->second;
		tileSet->second = 0;
	}
	m_tileSetMap.clear();
}

//Add a TileSet with a texture at the m_tileSetMap
bool fme::TileSetManager::addTileSet(std::string const& key, std::string const& path)
{
	//Load the texture
	sf::Texture* tile = new sf::Texture();
	if (!tile->loadFromFile(path)) {
		return false;
	}

	fme::TileSet* tileSet = new fme::TileSet(tile);

	m_tileSetMap.insert(std::pair <std::string, fme::TileSet *>(key, tileSet));
	return true;
}

//Load the vertexArray of a TileSet
void fme::TileSetManager::loadTileSet(std::string const& key, unsigned int maxSizeVertexArray, unsigned int level)
{
	m_tileSetMap[key]->loading(maxSizeVertexArray, level);
}

//Return a TileSet
fme::TileSet * fme::TileSetManager::getTileSet(std::string const& key)
{
	return m_tileSetMap[key];
}

void fme::TileSetManager::assembleContinousArrays()
{
	for (std::map<std::string, fme::TileSet*>::iterator tileSet = m_tileSetMap.begin();
		tileSet != m_tileSetMap.end(); ++tileSet)
	{
		tileSet->second->assembleContinousArray();
	}
}

void fme::TileSetManager::clearAllTileSets()
{
	for (std::map<std::string, fme::TileSet*>::iterator tileSet = m_tileSetMap.begin();
		tileSet != m_tileSetMap.end(); ++tileSet)
	{
		tileSet->second->clearAllLayers();
	}
}