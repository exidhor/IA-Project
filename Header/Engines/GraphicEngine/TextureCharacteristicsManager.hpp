/*!
* \file		TextureCharacteristicsManager.hpp
* \brief	Create and add a TextureCharacteristics in a map.
*			Allow to retreive them by its keys
* \author	Alemior, Exhidor
* \version	1.1
* \date		05/02/2016
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engines/GraphicEngine/TextureCharacteristics.hpp"
#include "Utilities/Vector2.hpp"

namespace fme
{
	class TextureCharacteristicsManager
	{
	public:
		TextureCharacteristicsManager();

		~TextureCharacteristicsManager();

		bool addTextureCharacteristics(
				std::string key,
				Vector2f const& tileSize,
				std::vector <Vector2f> texturePoints,
				double timePerFrame, 
				TileSet* tileSetTarget);

		bool addTextureCharacteristics(
				std::string key, 
				Vector2f const& tileSize,
				Vector2f oneTexturePoint,
				TileSet* tileSetTarget);

		TextureCharacteristics*	getTextureCharacteristics(std::string key);


	private:
		std::map < std::string, TextureCharacteristics*>::iterator	m_textureCharacteristicsIndex;
		std::map <std::string, TextureCharacteristics*>				m_textureCharacteristics;
	};
}