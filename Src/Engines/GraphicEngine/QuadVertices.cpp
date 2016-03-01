#include "Engines/GraphicEngine/QuadVertices.hpp"

/*!
* \brief Construct 4 m_vertices from a texture bounds which will represents a texture
* \brief set sf::Vertex to the 4 m_vertices of the rectangle
* \param a texture bounds
*/
fme::QuadVertices::QuadVertices(sf::FloatRect const& textureBounds)
{
	// left top
	m_vertices[0] = sf::Vertex(
		sf::Vector2f(0 , 0),
		sf::Vector2f(textureBounds.left, textureBounds.top)
		);

	// right top
	m_vertices[1] = sf::Vertex(
		sf::Vector2f(textureBounds.width, 0),
		sf::Vector2f(textureBounds.left + textureBounds.width, textureBounds.top)
		);

	// right bot
	m_vertices[2] = sf::Vertex(
		sf::Vector2f(textureBounds.width, textureBounds.height),
		sf::Vector2f(textureBounds.left + textureBounds.width, textureBounds.top + textureBounds.height)
		);

	// left bot
	m_vertices[3] = sf::Vertex(
		sf::Vector2f(0, textureBounds.height),
		sf::Vector2f(textureBounds.left, textureBounds.top + textureBounds.height)
		);

	recalculateGlobalBounds();
}

/*!
* \brief Construct 4 m_vertices from a fme::quadVertices
* \brief copy each sf::Vertex
* \param quadVertices model for the copy
*/
fme::QuadVertices::QuadVertices(fme::QuadVertices const& quadVertices)
{
	m_vertices[0].position.x = quadVertices.m_vertices[0].position.x;
	m_vertices[0].position.y = quadVertices.m_vertices[0].position.y;
	m_vertices[0].texCoords.x = quadVertices.m_vertices[0].texCoords.x;
	m_vertices[0].texCoords.y = quadVertices.m_vertices[0].texCoords.y;

	m_vertices[1].position.x = quadVertices.m_vertices[1].position.x;
	m_vertices[1].position.y = quadVertices.m_vertices[1].position.y;
	m_vertices[1].texCoords.x = quadVertices.m_vertices[1].texCoords.x;
	m_vertices[1].texCoords.y = quadVertices.m_vertices[1].texCoords.y;

	m_vertices[2].position.x = quadVertices.m_vertices[2].position.x;
	m_vertices[2].position.y = quadVertices.m_vertices[2].position.y;
	m_vertices[2].texCoords.x = quadVertices.m_vertices[2].texCoords.x;
	m_vertices[2].texCoords.y = quadVertices.m_vertices[2].texCoords.y;

	m_vertices[3].position.x = quadVertices.m_vertices[3].position.x;
	m_vertices[3].position.y = quadVertices.m_vertices[3].position.y;
	m_vertices[3].texCoords.x = quadVertices.m_vertices[3].texCoords.x;
	m_vertices[3].texCoords.y = quadVertices.m_vertices[3].texCoords.y;

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
	return fme::Vector2f(m_globalBounds.left, m_globalBounds.top);
}

/*!
* \return the global bounds
*/
sf::FloatRect const& fme::QuadVertices::getGlobalBounds()
{
	return m_globalBounds;
}

/*!
* \brief set the position of the left-top vertex of the global bounds
* \param the new position
*/
void fme::QuadVertices::setPosition(fme::Vector2f const& newPosition)
{
	sf::Vector2f offset(
		newPosition.x - m_globalBounds.left,
		newPosition.y - m_globalBounds.top
		);

	sf::Transform transformation;
	transformation.translate(offset);
	applyTranformation(transformation);
}

/*!
* \brief add m_vertices to the tileSet on the layel level target
* \param newTargetTileSet the tileSet which will display the m_vertices
* \param layerLevel the layer of display 
*/
void fme::QuadVertices::addVerticesToTheTileSet(fme::TileSet* newTargetTileSet,
	unsigned int layerLevel)
{
	newTargetTileSet->addVertices(m_vertices, layerLevel);
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
}

/*!
* \brief set a new texture from coordinates to the m_vertices
* \param newCoordTexture the new coordinate of the texture,
*			calculate from the top-left vertex of texture rectangle.
*			It needs to have the same size.
*/
void fme::QuadVertices::setTexture(fme::Vector2f const& newCoordTexture)
{
	float width = m_vertices[1].texCoords.x - m_vertices[0].texCoords.x;
	float height = m_vertices[3].texCoords.y - m_vertices[0].texCoords.y;
	
	m_vertices[0].texCoords = sf::Vector2f(
		newCoordTexture.x,
		newCoordTexture.y);
	
	m_vertices[1].texCoords = sf::Vector2f(
		newCoordTexture.x + width,
		newCoordTexture.y);

	m_vertices[2].texCoords = sf::Vector2f(
		newCoordTexture.x + width,
		newCoordTexture.y + height);

	m_vertices[3].texCoords = sf::Vector2f(
		newCoordTexture.x,
		newCoordTexture.y + height);
}

/*!
* \brief apply the transformation on the m_vertices by calculating their
* \brief new position.
* \param transformation all parameters for the transformation calculated
*			before
*/
void fme::QuadVertices::applyTranformation(sf::Transform const& transformation)
{
	for (unsigned int i = 0; i < 4; i++)
	{
		m_vertices[i].position = transformation.transformPoint(m_vertices[i].position);
	}

	recalculateGlobalBounds();
}

/*!
* \brief calculate the global bounds (i.e. the rectangle circumscribes the  
* \brief m_vertices transformed, parallel to the abscissa and ordinate)
*/
void fme::QuadVertices::recalculateGlobalBounds()
{
	float left = m_vertices[0].position.x;
	float right = m_vertices[0].position.x;

	float top = m_vertices[0].position.y;
	float bot = m_vertices[0].position.y;

	for (unsigned int i = 1; i < 4; i++)
	{
		if (left > m_vertices[i].position.x)
		{
			left = m_vertices[i].position.x;
		}
		else if (right < m_vertices[i].position.x)
		{
			right = m_vertices[i].position.x;
		}

		if (top > m_vertices[i].position.y)
		{
			top = m_vertices[i].position.y;
		}
		else if (bot < m_vertices[i].position.y)
		{
			bot = m_vertices[i].position.y;
		}
	}

	m_globalBounds.left = left;
	m_globalBounds.top = top;
	m_globalBounds.width = right - left;
	m_globalBounds.height = bot - top;
}