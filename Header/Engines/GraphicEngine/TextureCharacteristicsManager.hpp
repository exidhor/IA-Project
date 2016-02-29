/*!
* \file TextureCharacteristicsManager.hpp
* \brief Create and add a TextureCharacteritics in map of
* \brief Get a TextureCharacteistics by its key
* \author Alemior
* \version 1.1
* \date 05/02/2016
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engines/GraphicEngine/TextureCharacteristics.hpp"
#include "Engines/GraphicEngine/Vector2f.hpp"

namespace fme
{
	class TextureCharacteristicsManager
	{
	public:
		// Constructor
		TextureCharacteristicsManager();

		// Destructor
		~TextureCharacteristicsManager();

		// Add Methods
		bool addTextureCharacteristics(std::string key, Vector2f const& tileSize,
			std::vector <Vector2f> texturePoints, double timePerFrame, TileSet* tileSetTarget);
		bool addTextureCharacteristics(std::string key, Vector2f const& tileSize,
			Vector2f oneTexturePoint, TileSet* tileSetTarget);

		// Getter
		TextureCharacteristics* getTextureCharacteristics(std::string key);


	private:
		std::map < std::string, TextureCharacteristics*>::iterator textureCharacteristicsIndex;
		std::map <std::string, TextureCharacteristics*> textureCharacteristics;
	};
}