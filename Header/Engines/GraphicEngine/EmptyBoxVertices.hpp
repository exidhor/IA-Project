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
		EmptyBoxVertices(TextureVertices const& textureVertices);
		EmptyBoxVertices(EmptyBoxVertices const& emptyBoxVertices);
		~EmptyBoxVertices();

		virtual void setTexture(Vector2f const& newCoordTexture);

		virtual bool isEmptyBoxVertices();

		virtual const sf::Vertex* getConstVerticesArray() const;

	private:
		virtual sf::Vertex* getVerticesArray();
		virtual void computeGlobalBounds();

		sf::Vertex		m_vertices[8];
	};
}
