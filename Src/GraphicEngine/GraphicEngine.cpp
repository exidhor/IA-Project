#include "GraphicEngine/GraphicEngine.hpp"

fme::GraphicEngine::GraphicEngine()
{
	tileSetManager = NULL;
	textureCharactertisticsManager = NULL;
	ressourceManager = NULL;
	tileSetDisplayer = NULL;
}

fme::GraphicEngine::~GraphicEngine()
{
	delete tileSetDisplayer;
	delete ressourceManager;
	delete textureCharactertisticsManager;
	delete tileSetManager;
}

// ----------- initialization ---------------------------------------------------------

void fme::GraphicEngine::init()
{
	tileSetManager = new fme::TileSetManager();
	textureCharactertisticsManager = new fme::TextureCharacteristicsManager();
	ressourceManager = new fme::RessourceManager();
	tileSetDisplayer = new fme::TileSetsDisplayer();
}

// --------------- creation ---------------------------------------------------

void fme::GraphicEngine::addTileSet(std::string const& key, std::string const& path)
{
	if (!tileSetManager->addTileSet(key, path))
	{
		std::cerr << "ERROR during the loading of the texture\n"
			<< "\tkey :\t" << key
			<< "\tpath :\t" << path << std::endl;
	}
	else
	{
		ressourceManager->createKey(key);
		tileSetDisplayer->addTileSet(tileSetManager->getTileSet(key));
	}
}

void fme::GraphicEngine::initTileSetLayers(std::string const& key,
	unsigned int maxSizeArray,
	unsigned int numberOfLayer)
{
	tileSetManager->loadTileSet(key, maxSizeArray, numberOfLayer);
}

void fme::GraphicEngine::addTextureCharacteristics(
	std::string const& spriteKey,
	std::string const& tileSetKey,
	fme::Vector2f const& tileSize,
	std::vector <fme::Vector2f> texturePoints,
	double timePerFrame)
{
	if (!textureCharactertisticsManager->addTextureCharacteristics(
												spriteKey,
												tileSize,
												texturePoints,
												timePerFrame,
												tileSetManager->getTileSet(tileSetKey)
												))
	{
		if (ressourceManager->createKey(spriteKey))
		{
			std::cerr << "ERROR : duplicating keys in ressourceManager\n"
				<< "\tkey :\t" << spriteKey << std::endl;
		}
	}
}

void fme::GraphicEngine::addTextureCharacteristics(
	std::string const& spriteKey,
	std::string const& tileSetKey,
	fme::Vector2f const& tileSize,
	fme::Vector2f const& oneTexturePoint)
{
	if (!textureCharactertisticsManager->addTextureCharacteristics(
											spriteKey,
											tileSize,
											oneTexturePoint,
											tileSetManager->getTileSet(tileSetKey)
											))
	{
		if (ressourceManager->createKey(spriteKey))
		{
			std::cerr << "ERROR : duplicating keys in ressourceManager\n"
				<< "\tkey :\t" << spriteKey << std::endl;
		}
	}
}

void fme::GraphicEngine::addSprite(std::string const& key,
	unsigned int layerLevel,
	unsigned int numberOfElements)
{
	for (unsigned int i = 0; i < numberOfElements; i++)
	{
		ressourceManager->createSprite(
			key,
			textureCharactertisticsManager->getTextureCharacteristics(key),
			layerLevel
			);
	}
}

void fme::GraphicEngine::addAnimation(std::string const& key,
	unsigned int layerLevel,
	unsigned int numberOfElements)
{
	for (unsigned int i = 0; i < numberOfElements; i++)
	{
		ressourceManager->createAnimation(
			key,
			textureCharactertisticsManager->getTextureCharacteristics(key),
			layerLevel
			);
	}
}

fme::Sprite* fme::GraphicEngine::getFreeSprite(std::string const& key)
{
	return ressourceManager->getFreeSprite(key);
}

void fme::GraphicEngine::freeSpecificSprite(std::string const& key, unsigned int id)
{
	if (!ressourceManager->freeSpecificSprite(key, id))
	{
		std::cerr << "ERROR during the freeing of the sprite\n"
			<< "\tkey :\t" << key
			<< "\tid :\t" << id << std::endl;
	}
}

// -------------- animation gestion during the game ---------------------------------
void fme::GraphicEngine::update(double time)
{
	tileSetManager->clearAllTileSets();
	ressourceManager->updateAnimations(time);
	tileSetManager->assembleContinousArrays();
}

void fme::GraphicEngine::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	tileSetDisplayer->draw(target, states);
}


fme::RessourceManager * fme::GraphicEngine::getResourceManager() {
	return ressourceManager;
}