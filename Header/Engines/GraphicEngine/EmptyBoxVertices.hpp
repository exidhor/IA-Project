/*!
* \file		EmptyBoxVertices.hpp
* \brief	A rectangle represented only
*			by lines for its edges
* \author	Exhidor
* \version	0.1
* \date		2016-03-02
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engines/GraphicEngine/TileSet.hpp"
#include "Utilities/Vector2.hpp"
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

		// 8 because it's 2 for each edge
		sf::Vertex		m_vertices[8];
	};
}
