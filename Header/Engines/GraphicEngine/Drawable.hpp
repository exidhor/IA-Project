#pragma once
#include <SFML/Graphics.hpp>
#include "Engines/GraphicEngine/Vector2f.hpp"
#include "Engines/GraphicEngine/TileSet.hpp"

namespace fme
{
	class Drawable
	{
	public:
		Drawable();
		virtual ~Drawable();

		virtual void addToTileSet();

	private:

		TileSet*		m_tileSet;
		Vector2f		m_originCenteredRelative;
		unsigned int	m_layerLevelOfDisplay;
		bool			m_isHide;
	};
}
