/*!
* \file QuadVertices.hpp
* \brief 4 vertices which describes a textured sprite
* \brief It provides translation and rotation
* \author Exhidor
* \version 1.5
* \date 2016-02-01
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GraphicEngine/TileSet.hpp"
#include "GraphicEngine/Vector2f.hpp"

namespace fme
{
	class QuadVertices
	{
	public:
		QuadVertices(sf::FloatRect const& textureBounds);
		QuadVertices(QuadVertices const& quadVertices);
		~QuadVertices();

		void addVerticesToTheTileSet(TileSet* targetTileSet, unsigned int layerLevel);

		// getters

		Vector2f getPosition();
		sf::FloatRect const& getGlobalBounds();

		// setters

		void setPosition(Vector2f const& newPosition);
		void setTexture(Vector2f const& newCoordTexture);

		// transformation

		void translate(Vector2f const& offset, sf::Transform & transformation);
		void rotate(float angleOfRotation, Vector2f const& originOfTheRotation,
			sf::Transform & transformation);
		void applyTranformation(sf::Transform const& transformation);

	private:
		void recalculateGlobalBounds();

		sf::Vertex vertices[4];
		sf::FloatRect globalBounds;
	};
}