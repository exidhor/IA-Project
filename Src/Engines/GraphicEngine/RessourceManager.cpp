#include "Engines/GraphicEngine/RessourceManager.hpp"

fme::RessourceManager::RessourceManager()
{
	// void 
}

fme::RessourceManager::~RessourceManager()
{
	// TO DO
}

bool fme::RessourceManager::createKey(std::string const& key)
{
	// check if the key exists
	m_ressourceArrayIndex = getIterator(key);
	if (m_ressourceArrayIndex != m_ressources.end()) {
		return true;
	}

	// create a new array from the new key
	m_ressources.emplace(key, std::vector <fme::Ressource>());
	return false;
}

bool fme::RessourceManager::createSprite(
	std::string const& key,
	fme::TextureCharacteristics* animationCharacteristic,
	unsigned int layerLevel,
	unsigned int numberOfElements)
{
	// check if the key exists
	m_ressourceArrayIndex = getIterator(key);
	if (m_ressourceArrayIndex == m_ressources.end()) {
		return false;
	}

	// create n sprites in the array
	for (unsigned int i = 0; i < numberOfElements; i++)
	{
		m_ressourceArrayIndex->second.push_back(
			fme::Ressource(new fme::Sprite(animationCharacteristic, layerLevel))
			);
	}
	return true;
}

bool fme::RessourceManager::createAnimation(
	std::string const& key,
	fme::TextureCharacteristics* animationCharacteristic,
	unsigned int layerLevel,
	unsigned int numberOfElements)
{
	// check if the key exists
	m_ressourceArrayIndex = getIterator(key);
	if (m_ressourceArrayIndex == m_ressources.end()) {
		return false;
	}

	// create n animations in the array
	for (unsigned int i = 0; i < numberOfElements; i++)
	{
		m_ressources[key].push_back(
			fme::Ressource(new fme::Animation(animationCharacteristic, layerLevel))
			);
	}

	return true;
}

fme::Sprite* fme::RessourceManager::getFreeSprite(std::string const& key)
{
	// check if the key exists
	m_ressourceArrayIndex = getIterator(key);
	if (m_ressourceArrayIndex == m_ressources.end()) {
		return NULL;
	}

	// check if there is a non used sprite
	for (unsigned int i = 0; i < m_ressourceArrayIndex->second.size(); i++)
	{
		// return the adress of the free sprite
		if (!m_ressourceArrayIndex->second[i].isUsed)
		{
			// set the variable isUsed to show that this object is busy
			m_ressourceArrayIndex->second[i].isUsed = true;
			return m_ressources[key][i].sprite;
		}
	}

	// create a sprite if all sprites are busy

	// check if there is an another element to copy it
	if (m_ressourceArrayIndex->second.size() == 0)
	{
		return NULL;
	}

	fme::Sprite* newSprite = NULL;

	// check if we need construct a fme::Sprite or an fme::Animation
	if (m_ressourceArrayIndex->second[0].sprite->isSprite())
	{
		// create a copy fme::Sprite from the first element
		newSprite = new fme::Sprite(*m_ressourceArrayIndex->second[0].sprite);
	}
	else
	{
		// create an fme::Animation by casting the first element in fme::Animation
		newSprite = new fme::Animation(*(fme::Animation*)m_ressourceArrayIndex->second[0].sprite);
	}

	// add the new objet to the map
	m_ressources[key].push_back(fme::Ressource(newSprite));

	// set the variable isUsed to show that this object is busy
	m_ressourceArrayIndex->second[m_ressourceArrayIndex->second.size()-1].isUsed = true;

	// return the address of the object
	return newSprite;
}

fme::Sprite* fme::RessourceManager::getSpecificSprite(std::string const& key, unsigned int id)
{
	// check if the key exists
	m_ressourceArrayIndex = getIterator(key);
	if (m_ressourceArrayIndex == m_ressources.end()) {
		return NULL;
	}

	// check if the id exists
	if (m_ressourceArrayIndex->second.size() <= id)
	{
		return NULL;
	}

	// return the address of the sprite at the index id
	return m_ressourceArrayIndex->second[id].sprite;
}


bool fme::RessourceManager::freeSpecificSprite(std::string const& key, unsigned int id)
{
	m_ressourceArrayIndex = getIterator(key);
	if (m_ressourceArrayIndex != m_ressources.end()) {
		if (m_ressourceArrayIndex->second.size() >= id)
		{
			m_ressourceArrayIndex->second[id].isUsed = false;
			return true;
		}
	}
	return false;
}

void fme::RessourceManager::updateAnimations(double time)
{
	for (std::map<std::string, std::vector<fme::Ressource>>::iterator animation = m_ressources.begin();
		animation != m_ressources.end(); ++animation)
	{
		for (unsigned int i = 0; i < animation->second.size(); i++)
		{
			if (animation->second[i].isUsed)
			{
				animation->second[i].sprite->actualize(time);
				animation->second[i].sprite->addToTileSet();
			}
		}
	}
}

std::map <std::string, std::vector <fme::Ressource> >::iterator fme::RessourceManager::getIterator(
	std::string const& key)
{
	return m_ressources.find(key);
}