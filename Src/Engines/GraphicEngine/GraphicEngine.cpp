#include "Engines/GraphicEngine/GraphicEngine.hpp"

fme::GraphicEngine::GraphicEngine()
{
	m_tileSetManager = NULL;
	m_textureCharactertisticsManager = NULL;
	m_ressourceManager = NULL;
	m_tileSetDisplayer = NULL;
	m_frameTime = 0;
	m_mergeFrameTime = 0;
	m_windowIsOpen = false;
}

fme::GraphicEngine::~GraphicEngine()
{
	if (m_tileSetDisplayer != NULL)
	{
		delete m_tileSetDisplayer;
	}

	if (m_ressourceManager != NULL)
	{
		delete m_ressourceManager;
	}

	if (m_textureCharactertisticsManager != NULL)
	{
		delete m_textureCharactertisticsManager;
	}

	if (m_tileSetManager != NULL)
	{
		delete m_tileSetManager;
	}

	if (m_window != NULL)
	{
		delete m_window;
	}
}

// ----------- initialization ------------------------------------------------------

void fme::GraphicEngine::init()
{
	m_tileSetManager = new fme::TileSetManager();
	m_textureCharactertisticsManager = new fme::TextureCharacteristicsManager();
	m_ressourceManager = new fme::RessourceManager();
	m_tileSetDisplayer = new fme::TileSetsDisplayer();
}

void fme::GraphicEngine::openWindow(std::string const& title)
{
	m_window = new sf::RenderWindow(sf::VideoMode(1000, 600), title);
	m_windowIsOpen = true;
	m_window->setActive(false);
}

void fme::GraphicEngine::closeWindow()
{
	m_windowIsOpen = false;
}

void fme::GraphicEngine::setFrameRate(float framePerSecond)
{
	m_frameTime = 1. / framePerSecond;
	m_mergeFrameTime = m_frameTime * (0.7 / 60);
}

// ----------------- use ----------------------------------------------------------

void fme::GraphicEngine::run(int framePerSecond)
{
	setFrameRate(framePerSecond);

	sf::Clock clock;
	double timeSpent = 0;
	double offsetTime = 0;

	while (m_windowIsOpen)
	{
		timeSpent = clock.getElapsedTime().asSeconds();
		offsetTime = m_frameTime - (timeSpent + m_mergeFrameTime);

		if (offsetTime < 0)
		{
			update(timeSpent);

			m_window->clear();
			m_window->draw(*this);
			m_window->display();
			clock.restart();
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::microseconds((long)offsetTime * 1000000));
		}
	}
}

// --------------- creation -------------------------------------------------------

void fme::GraphicEngine::addTileSet(std::string const& key, std::string const& path)
{
	if (!m_tileSetManager->addTileSet(key, path))
	{
		std::cerr << "ERROR during the loading of the texture\n"
			<< "\tkey :\t" << key
			<< "\tpath :\t" << path << std::endl;
	}
	else
	{
		m_ressourceManager->createKey(key);
		m_tileSetDisplayer->addTileSet(m_tileSetManager->getTileSet(key));
	}
}

void fme::GraphicEngine::initTileSetLayers(std::string const& key,
	unsigned int maxSizeArray,
	unsigned int numberOfLayer)
{
	m_tileSetManager->loadTileSet(key, maxSizeArray, numberOfLayer);
}

void fme::GraphicEngine::addTileSet(std::string const& key, 
	std::string const& path,
	unsigned int maxSizeArray,
	unsigned int numberOfLayer)
{
	addTileSet(key, path);
	initTileSetLayers(key, maxSizeArray, numberOfLayer);
}

void fme::GraphicEngine::addTextureCharacteristics(
	std::string const& spriteKey,
	std::string const& tileSetKey,
	Vector2f const& tileSize,
	std::vector <Vector2f> texturePoints,
	double timePerFrame)
{
	if (!m_textureCharactertisticsManager->addTextureCharacteristics(
												spriteKey,
												tileSize,
												texturePoints,
												timePerFrame,
												m_tileSetManager->getTileSet(tileSetKey)
												))
	{
		if (m_ressourceManager->createKey(spriteKey))
		{
			std::cerr << "ERROR : duplicating keys in m_ressourceManager\n"
				<< "\tkey :\t" << spriteKey << std::endl;
		}
	}
}

void fme::GraphicEngine::addTextureCharacteristics(
	std::string const& spriteKey,
	std::string const& tileSetKey,
	Vector2f const& tileSize,
	Vector2f const& oneTexturePoint)
{
	if (!m_textureCharactertisticsManager->addTextureCharacteristics(
											spriteKey,
											tileSize,
											oneTexturePoint,
											m_tileSetManager->getTileSet(tileSetKey)
											))
	{
		if (m_ressourceManager->createKey(spriteKey))
		{
			std::cerr << "ERROR : duplicating keys in m_ressourceManager\n"
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
		m_ressourceManager->createSprite(
			key,
			m_textureCharactertisticsManager->getTextureCharacteristics(key),
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
		m_ressourceManager->createAnimation(
			key,
			m_textureCharactertisticsManager->getTextureCharacteristics(key),
			layerLevel
			);
	}
}

fme::Sprite* fme::GraphicEngine::getFreeSprite(std::string const& key)
{
	return m_ressourceManager->getFreeSprite(key);
}

void fme::GraphicEngine::freeSpecificSprite(std::string const& key, unsigned int id)
{
	if (!m_ressourceManager->freeSpecificSprite(key, id))
	{
		std::cerr << "ERROR during the freeing of the sprite\n"
			<< "\tkey :\t" << key
			<< "\tid :\t" << id << std::endl;
	}
}

// -------------- animation gestion during the game ---------------------------------

void fme::GraphicEngine::update(double time)
{
	m_tileSetManager->clearAllTileSets();
	m_ressourceManager->updateAnimations(time);
	m_tileSetManager->assembleContinousArrays();
}

void fme::GraphicEngine::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	m_tileSetDisplayer->draw(target, states);
}


fme::RessourceManager * fme::GraphicEngine::getResourceManager() {
	return m_ressourceManager;
}