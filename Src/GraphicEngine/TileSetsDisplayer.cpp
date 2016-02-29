#include "GraphicEngine/TileSetsDisplayer.hpp"

fme::TileSetsDisplayer::TileSetsDisplayer()
{
	// void
}

void fme::TileSetsDisplayer::addTileSet(fme::TileSet* tileSet)
{
	tileSetArray.push_back(tileSet);
}

void fme::TileSetsDisplayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (unsigned int i = 0; i < tileSetArray.size(); i++)
	{
		tileSetArray[i]->draw(target, states);
	}
}