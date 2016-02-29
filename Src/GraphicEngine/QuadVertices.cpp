#include "GraphicEngine/QuadVertices.hpp"

/*!
* \brief Construct 4 vertices from a texture bounds which will represents a texture
* \brief set sf::Vertex to the 4 vertices of the rectangle
* \param a texture bounds
*/
fme::QuadVertices::QuadVertices(sf::FloatRect const& textureBounds)
{
	// left top
	vertices[0] = sf::Vertex(
		sf::Vector2f(0 , 0),
		sf::Vector2f(textureBounds.left, textureBounds.top)
		);

	// right top
	vertices[1] = sf::Vertex(
		sf::Vector2f(textureBounds.width, 0),
		sf::Vector2f(textureBounds.left + textureBounds.width, textureBounds.top)
		);

	// right bot
	vertices[2] = sf::Vertex(
		sf::Vector2f(textureBounds.width, textureBounds.height),
		sf::Vector2f(textureBounds.left + textureBounds.width, textureBounds.top + textureBounds.height)
		);

	// left bot
	vertices[3] = sf::Vertex(
		sf::Vector2f(0, textureBounds.height),
		sf::Vector2f(textureBounds.left, textureBounds.top + textureBounds.height)
		);

	recalculateGlobalBounds();
}

/*!
* \brief Construct 4 vertices from a fme::quadVertices
* \brief copy each sf::Vertex
* \param quadVertices model for the copy
*/
fme::QuadVertices::QuadVertices(fme::QuadVertices const& quadVertices)
{
	vertices[0].position.x = quadVertices.vertices[0].position.x;
	vertices[0].position.y = quadVertices.vertices[0].position.y;
	vertices[0].texCoords.x = quadVertices.vertices[0].texCoords.x;
	vertices[0].texCoords.y = quadVertices.vertices[0].texCoords.y;

	vertices[1].position.x = quadVertices.vertices[1].position.x;
	vertices[1].position.y = quadVertices.vertices[1].position.y;
	vertices[1].texCoords.x = quadVertices.vertices[1].texCoords.x;
	vertices[1].texCoords.y = quadVertices.vertices[1].texCoords.y;

	vertices[2].position.x = quadVertices.vertices[2].position.x;
	vertices[2].position.y = quadVertices.vertices[2].position.y;
	vertices[2].texCoords.x = quadVertices.vertices[2].texCoords.x;
	vertices[2].texCoords.y = quadVertices.vertices[2].texCoords.y;

	vertices[3].position.x = quadVertices.vertices[3].position.x;
	vertices[3].position.y = quadVertices.vertices[3].position.y;
	vertices[3].texCoords.x = quadVertices.vertices[3].texCoords.x;
	vertices[3].texCoords.y = quadVertices.vertices[3].texCoords.y;

	recalculateGlobalBounds();
}


/*!
* \brief Destruct the object
*/
fme::QuadVertices::~QuadVertices()
{
	// void
}

/*!
* \return the position of the left-top vertex of the global bounds
*/
fme::Vector2f fme::QuadVertices::getPosition()
{
	return fme::Vector2f(globalBounds.left, globalBounds.top);
}

/*!
* \return the global bounds
*/
sf::FloatRect const& fme::QuadVertices::getGlobalBounds()
{
	return globalBounds;
}

/*!
* \brief set the position of the left-top vertex of the global bounds
* \param the new position
*/
void fme::QuadVertices::setPosition(fme::Vector2f const& newPosition)
{
	sf::Vector2f offset(
		newPosition.x - globalBounds.left,
		newPosition.y - globalBounds.top
		);

	sf::Transform transformation;
	transformation.translate(offset);
	applyTranformation(transformation);
}

/*!
* \brief add vertices to the tileSet on the layel level target
* \param newTargetTileSet the tileSet which will display the vertices
* \param layerLevel the layer of display 
*/
void fme::QuadVertices::addVerticesToTheTileSet(fme::TileSet* newTargetTileSet,
	unsigned int layerLevel)
{
	newTargetTileSet->addVertices(vertices, layerLevel);
}

/*!
* \brief calculate a rotation on the sf::Tranform transformation
* \param angleOfRotation in degree
* \param origin the origin of the rotation
* \param transformation the actual parameters of the final transformation
*			where the rotation will be apply
*/
void fme::QuadVertices::rotate(float angleOfRotation, fme::Vector2f const& origin,
	sf::Transform & transformation)
{
	transformation.rotate(
		angleOfRotation,
		origin.x,
		origin.y
		);
	//applyTranformation(transformation);
}

/*!
* \brief calculate a translation on the sf::Tranform transformation
* \param offset the offset of the translation
* \param transformation the actual parameters of the final transformation
*			where the translation will be apply
*/
void fme::QuadVertices::translate(fme::Vector2f const& offset, sf::Transform & transformation)
{
	transformation.translate(offset.x, offset.y);
	//applyTranformation(transformation);
}

/*!
* \brief set a new texture from coordinates to the vertices
* \param newCoordTexture the new coordinate of the texture,
*			calculate from the top-left vertex of texture rectangle.
*			It needs to have the same size.
*/
void fme::QuadVertices::setTexture(fme::Vector2f const& newCoordTexture)
{
	float width = vertices[1].texCoords.x - vertices[0].texCoords.x;
	float height = vertices[3].texCoords.y - vertices[0].texCoords.y;
	
	vertices[0].texCoords = sf::Vector2f(newCoordTexture.x, newCoordTexture.y);
	
	vertices[1].texCoords = sf::Vector2f(
		newCoordTexture.x + width,
		newCoordTexture.y
		);

	vertices[2].texCoords = sf::Vector2f(
		newCoordTexture.x + width,
		newCoordTexture.y + height
		);

	vertices[3].texCoords = sf::Vector2f(
		newCoordTexture.x,
		newCoordTexture.y + height
		);
}

/*!
* \brief apply the transformation on the vertices by calculating their
* \brief new position.
* \param transformation all parameters for the transformation calculated
*			before
*/
void fme::QuadVertices::applyTranformation(sf::Transform const& transformation)
{
	for (unsigned int i = 0; i < 4; i++)
	{
		vertices[i].position = transformation.transformPoint(vertices[i].position);
	}

	recalculateGlobalBounds();
}

/*!
* \brief calculate the global bounds (i.e. the rectangle circumscribes the  
* \brief vertices transformed, parallel to the absciss and ordinate)
*/
void fme::QuadVertices::recalculateGlobalBounds()
{
	float left = vertices[0].position.x;
	float right = vertices[0].position.x;

	float top = vertices[0].position.y;
	float bot = vertices[0].position.y;

	for (unsigned int i = 1; i < 4; i++)
	{
		if (left > vertices[i].position.x)
		{
			left = vertices[i].position.x;
		}
		else if (right < vertices[i].position.x)
		{
			right = vertices[i].position.x;
		}

		if (top > vertices[i].position.y)
		{
			top = vertices[i].position.y;
		}
		else if (bot < vertices[i].position.y)
		{
			bot = vertices[i].position.y;
		}
	}

	globalBounds.left = left;
	globalBounds.top = top;
	globalBounds.width = right - left;
	globalBounds.height = bot - top;
}