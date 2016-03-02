#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Engines/GraphicEngine/TileSet.hpp"
#include "Engines/GraphicEngine/Vector2f.hpp"

namespace fme
{
	class TextureVertices
	{
	public :
		TextureVertices(int numberOfVertex = 0);
		TextureVertices(TextureVertices const& textureVertices);
		virtual ~TextureVertices();

		void addVerticesToTheTileSet(TileSet* targetTileSet, unsigned int layerLevel);

		Vector2f		getPosition();
		sf::FloatRect	const& getGlobalBounds();

		void setPosition(Vector2f const& newPosition);
		virtual void setTexture(Vector2f const& newCoordTexture) = 0;
		void setColor(sf::Color const& color);

		void translate(Vector2f const& offset, sf::Transform & transformation);
		void rotate(float angleOfRotation, Vector2f const& originOfTheRotation,
			sf::Transform & transformation);
		void applyTranformation(sf::Transform const& transformation);
		
	protected :
		virtual sf::Vertex* getVerticesArray() = 0;
		virtual void computeGlobalBounds() = 0;

		void setSizeGlobalBounds(float width, float height);
		void globalBoundsIsComputed();
		void setSizeArray(unsigned int newSize);
		
	private :
		void checkUpdateGlobalBounds();

		unsigned int	m_size;
		sf::FloatRect	m_globalBounds;
		bool			m_globalBoundsUpToDate;
	};
}