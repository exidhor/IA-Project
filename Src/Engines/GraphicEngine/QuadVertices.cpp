#include "Engines/GraphicEngine/QuadVertices.hpp"

/*!
* \brief Construct 4 m_vertices from a texture bounds which will represents a texture
* \brief set sf::Vertex to the 4 m_vertices of the rectangle
* \param a texture bounds
*/
fme::QuadVertices::QuadVertices(sf::FloatRect const& textureBounds)
	: TextureVertices(4)
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

	computeGlobalBounds();
}

fme::QuadVertices::QuadVertices(TextureVertices const& textureVertices)
	: TextureVertices(textureVertices)
{
	for (unsigned int i = 0; i < 4; i++)
	{
		m_vertices[i] = textureVertices.getConstVerticesArray()[i];
	}
}

/*!
* \brief Construct 4 m_vertices from a fme::quadVertices
* \brief copy each sf::Vertex
* \param quadVertices model for the copy
*/
fme::QuadVertices::QuadVertices(fme::QuadVertices const& quadVertices)	
	: TextureVertices(quadVertices)
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
}


/*!
* \brief Destruct the object
*/
fme::QuadVertices::~QuadVertices()
{
	delete[] m_vertices;
}


/*!
* \brief set a new texture from coordinates to the m_vertices
* \param newCoordTexture the new coordinate of the texture,
*			calculate from the top-left vertex of texture rectangle.
*			It needs to have the same size.
*/
void fme::QuadVertices::setTexture(Vector2f const& newCoordTexture)
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
* \brief calculate the global bounds (i.e. the rectangle circumscribes the  
* \brief m_vertices transformed, parallel to the abscissa and ordinate)
*/
void fme::QuadVertices::computeGlobalBounds()
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

	setPosition(Vector2f(left, top));
	setSizeGlobalBounds(right - left, bot - top);

	globalBoundsIsComputed();
}

sf::Vertex* fme::QuadVertices::getVerticesArray()
{
	return m_vertices;
}

bool fme::QuadVertices::isQuadVertices()
{
	return true;
}

const sf::Vertex* fme::QuadVertices::getConstVerticesArray() const
{
	return m_vertices;
}