/*!
* \file		Drawable.hpp
* \brief	An object with a shape and 
*			a texture/color which can
*			be drawn
* \author	Exhidor
* \version	0.1
* \date		2016-03-02
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "Utilities/Vector2.hpp"
#include "Engines/GraphicEngine/TileSet.hpp"
#include "Engines/GraphicEngine/TextureVertices.hpp"
#include "Engines/GraphicEngine/QuadVertices.hpp"
#include "Engines/GraphicEngine/EmptyBoxVertices.hpp"

namespace fme
{
	class Drawable
	{
	public:
		Drawable();
		Drawable(Drawable const& drawableObject);
		virtual ~Drawable();

		void initTileSet(TileSet* tileSet);
		void initVertices(TextureVertices* vertices);

		virtual void addToTileSet();

		Vector2f getPosition();
		Vector2f getGlobalSize();

		void setPosition(Vector2f const position);
		void setPosition(float abscissa, float ordinate);
		void move(float offsetX, float offsetY);
		void setLayerLevel(unsigned int layerLevel);

		void hide();
		void show();

	protected:
		void initOriginCenteredRelative(int abscissa, int ordinate);

		void setTexture(Vector2f const& newCoordTexture);
		void setColor(sf::Color const& color);

	private:
		TextureVertices*	m_vertices;
		TileSet*			m_tileSet;
		Vector2f			m_originCenteredRelative;
		unsigned int		m_layerLevelOfDisplay;
		bool				m_isHidden;
	};
}
