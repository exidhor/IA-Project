#include "Engines/GraphicEngine/TileSetsDisplayer.hpp"

fme::TileSetsDisplayer::TileSetsDisplayer()
{
	// void
}

void fme::TileSetsDisplayer::addTileSet(fme::TileSet* tileSet)
{
	m_tileSetArray.push_back(tileSet);
}

void fme::TileSetsDisplayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (unsigned int i = 0; i < m_tileSetArray.size(); i++)
	{
		m_tileSetArray[i]->draw(target, states);
	}
}