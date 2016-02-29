/*!
* \file TextureCharacteristics.hpp
* \brief All the characteristics necessary to build
* \brief an Animation.
* \brief store an array of TilesCharacteristics and the
* \brief TileSet used
* \author Alemior / Exhidor
* \version 1.5
* \date 2016-02-01
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engines/GraphicEngine/TilesCharacteristics.hpp"
#include "Engines/GraphicEngine/TileSet.hpp"
#include "Engines/GraphicEngine/Vector2f.hpp"

namespace fme
{
	class TextureCharacteristics
	{
	public:
		TextureCharacteristics(
			std::vector <TilesCharacteristics*> tilesCharacteristics,
			TileSet* tileSet);
		TextureCharacteristics(
			TilesCharacteristics* tileCharacteristics,
			TileSet* tileSet);

		~TextureCharacteristics();

		void addTilesCharacteristics(TilesCharacteristics* newArray);

		//Getters
		TileSet* getTileSet() const;
		Vector2f const& getTileSize(unsigned int indexTileCharac)  const;
		Vector2f const& getTexturePoints(unsigned int indexCulumn, unsigned int indexLine)  const;
		unsigned int getLineSizeOf(unsigned int indexTileCharac)  const;
		unsigned int getCulumnSize()  const;
		double getTimePerFrame(unsigned int indexTileCharac)  const;

	private:
		std::vector <TilesCharacteristics*> arrayOfTileCharacteristic;
		TileSet* tileSet;
	};
}