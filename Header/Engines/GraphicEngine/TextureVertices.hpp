/*!
* \file		TextureVertices.hpp
* \brief	Vertices array which represents a shape.
*			get globalBounds and can be transformed
* \author	Exhidor
* \version	0.1
* \date		02/03/2016
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Engines/GraphicEngine/TileSet.hpp"
#include "Utilities/Vector2.hpp"

namespace fme
{
	class TextureVertices
	{
	public :
		TextureVertices(int numberOfVertex = 0);
		TextureVertices(TextureVertices const& textureVertices);
		virtual ~TextureVertices();

		void			addVerticesToTheTileSet(TileSet* targetTileSet, unsigned int layerLevel);

		Vector2f		getPosition();
		sf::FloatRect	const& getGlobalBounds();

		virtual void	setTexture(Vector2f const& newCoordTexture) = 0;
		void			setPosition(Vector2f const& newPosition);
		void			setColor(sf::Color const& color);

		void			translate(Vector2f const& offset, sf::Transform & transformation);
		void			rotate(float angleOfRotation, Vector2f const& originOfTheRotation,
							sf::Transform & transformation);
		void			applyTranformation(sf::Transform const& transformation);

		// used to well copy vertices
		virtual bool	isQuadVertices();
		virtual bool	isEmptyBoxVertices();
		virtual const	sf::Vertex* getConstVerticesArray() const = 0;

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