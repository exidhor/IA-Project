#pragma once
#include <SFML/Graphics.hpp>
#include "Engines/GraphicEngine/TileSet.hpp"
#include "Engines/GraphicEngine/Vector2f.hpp"

namespace fme
{
	class TextureVertices
	{
	public :
		TextureVertices(int numberOfVertex);

		void addVerticesToTheTileSet(TileSet* targetTileSet, unsigned int layerLevel);

		Vector2f		getPosition();
		sf::FloatRect	const& getGlobalBounds();

		void setPosition(Vector2f const& newPosition);
		void setTexture(Vector2f const& newCoordTexture);

		void translate(Vector2f const& offset, sf::Transform & transformation);
		void rotate(float angleOfRotation, Vector2f const& originOfTheRotation,
			sf::Transform & transformation);
		void applyTranformation(sf::Transform const& transformation);
		
	protected :
		void recalculateGlobalBounds();
		
	private :
		sf::Vertex*		m_vertices;
		sf::FloatRect	m_globalBounds;
	};
}