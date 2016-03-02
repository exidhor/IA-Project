#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engines/GraphicEngine/TileSet.hpp"
#include "Engines/GraphicEngine/Vector2f.hpp"
#include "Engines/GraphicEngine/TextureVertices.hpp"

namespace fme
{
	class EmptyBoxVertices : public TextureVertices
	{
	public:
		EmptyBoxVertices(sf::FloatRect const& boxBounds);
		EmptyBoxVertices(EmptyBoxVertices const& emptyBoxVertices);
		~EmptyBoxVertices();

		virtual void setTexture(Vector2f const& newCoordTexture);

	private:
		virtual sf::Vertex* getVerticesArray();
		virtual void computeGlobalBounds();

		sf::Vertex		m_vertices[8];
	};
}
