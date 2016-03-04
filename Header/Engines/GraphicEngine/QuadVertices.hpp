/*!
* \file		QuadVertices.hpp
* \brief	4 vertices which describes a textured sprite
*			this group is a rectangle
* \author	Exhidor
* \version	2.0
* \date		2016-02-01
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engines/GraphicEngine/TileSet.hpp"
#include "Utilities/Vector2.hpp"
#include "Engines/GraphicEngine/TextureVertices.hpp"

namespace fme
{
	class QuadVertices : public TextureVertices
	{
	public:
		QuadVertices(sf::FloatRect const& textureBounds);
		QuadVertices(TextureVertices const& textureVertices);
		QuadVertices(QuadVertices const& quadVertices);
		~QuadVertices();

		virtual void setTexture(Vector2f const& newCoordTexture);

		virtual bool isQuadVertices();

		virtual const sf::Vertex* getConstVerticesArray() const;

	private:
		virtual sf::Vertex* getVerticesArray();
		virtual void computeGlobalBounds();

		sf::Vertex		m_vertices[4];
	};
}