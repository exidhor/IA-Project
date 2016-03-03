/*!
* \file		RessourceManager.hpp
* \brief	Manage the ressources to
*			avoid useless copy of elements
*			and minimize memory use
* \author	Exhidor
* \version	0.1
* \date		2016-02-01
*/

#pragma once
#include <map>
#include <vector>
#include <string>
#include "Engines/GraphicEngine/Sprite.hpp"
#include "Engines/GraphicEngine/Animation.hpp"
#include "Engines/GraphicEngine/TextureCharacteristics.hpp"
#include "Engines/GraphicEngine/Ressource.hpp"

namespace fme
{
	class RessourceManager
	{
	public:
		RessourceManager();
		~RessourceManager();

		//create methods
		bool	createKey(std::string const& key);
		
		bool	createSprite(
					std::string const& key,
					TextureCharacteristics* animationCharacteristic,
					unsigned int layerLevel,
					unsigned int numberOfElements = 1);
		
		bool	createAnimation(
					std::string const& key,
					TextureCharacteristics* animationCharacteristic,
					unsigned int layerLevel,
					unsigned int numberOfElements = 1);

		// get a free sprite
		Sprite* getFreeSprite(std::string const& key);

		// get a specific sprite
		Sprite* getSpecificSprite(std::string const& key, unsigned int id);

		// free a ressource
		bool	freeSpecificSprite(std::string const& key, unsigned int id);

		// time gestion
		void	updateAnimations(double time);

	private:
		std::map <std::string, std::vector <Ressource> >::iterator
			getIterator(std::string const& key);

		std::map 
			< std::string, std::vector < Ressource > >::iterator	m_ressourceArrayIndex;
		std::map <std::string, std::vector <Ressource> >			m_ressources;
	};
}