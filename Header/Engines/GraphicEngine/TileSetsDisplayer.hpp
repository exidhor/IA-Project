/*!
* \file		TileSetsDisplayer.hpp
* \brief	It manage all TileSet to be drawn
*			in the right order.
* \author	Exhidor
* \version	0.1
* \date		2016-02-01
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Engines/GraphicEngine/TileSet.hpp"

namespace fme
{
	class TileSetsDisplayer : public sf::Drawable
	{
	public:
		TileSetsDisplayer();

		void			addTileSet(TileSet* tileSet);

		virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		std::vector <TileSet*> m_tileSetArray;
	};
}