#pragma once
#include <map>
#include <vector>
#include <string>
#include "GraphicEngine/Sprite.hpp"
#include "GraphicEngine/Animation.hpp"
#include "GraphicEngine/TextureCharacteristics.hpp"
#include "GraphicEngine/Ressource.hpp"

namespace fme
{
	class RessourceManager
	{
	public:
		RessourceManager();
		~RessourceManager();

		//create methods
		bool createKey(std::string const& key);
		
		bool createSprite(
			std::string const& key,
			TextureCharacteristics* animationCharacteristic,
			unsigned int layerLevel,
			unsigned int numberOfElements = 1);
		
		bool createAnimation(
			std::string const& key,
			TextureCharacteristics* animationCharacteristic,
			unsigned int layerLevel,
			unsigned int numberOfElements = 1);

		// get a free sprite
		Sprite* getFreeSprite(std::string const& key);

		// get a specific sprite
		Sprite* getSpecificSprite(std::string const& key, unsigned int id);

		// free a ressource
		bool freeSpecificSprite(std::string const& key, unsigned int id);

		// time gestion
		void updateAnimations(double time);

	private:
		std::map <std::string, std::vector <Ressource> >::iterator getIterator(
			std::string const& key);

		std::map <std::string, std::vector <Ressource> > ressources;
		std::map < std::string,
			std::vector < Ressource >> ::iterator ressourceArrayIndex;
	};
}