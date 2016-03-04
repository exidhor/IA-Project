#include "Engines/GraphicEngine/TextureVertices.hpp"

fme::TextureVertices::TextureVertices(int numberOfVertex)
{
	m_size = numberOfVertex;
	m_globalBoundsUpToDate = false;
}

fme::TextureVertices::TextureVertices(TextureVertices const& textureVertices)
{
	m_size = textureVertices.m_size;
	if (textureVertices.m_globalBoundsUpToDate)
	{
		m_globalBounds = textureVertices.m_globalBounds;
		m_globalBoundsUpToDate = true;
	}
	else
	{
		m_globalBoundsUpToDate = false;
	}
}

fme::TextureVertices::~TextureVertices()
{
	// void
}

/*!
* \brief add m_vertices to the tileSet on the layel level target
* \param newTargetTileSet the tileSet which will display the m_vertices
* \param layerLevel the layer of display
*/
void fme::TextureVertices::addVerticesToTheTileSet(TileSet* targetTileSet, 
													unsigned int layerLevel)
{
	targetTileSet->addVertices(getVerticesArray(), m_size, layerLevel);
}

/*!
* \return the position of the left-top vertex of the global bounds
*/
Vector2f fme::TextureVertices::getPosition()
{
	checkUpdateGlobalBounds();

	return Vector2f(m_globalBounds.left, m_globalBounds.top);
}

/*!
* \return the global bounds
*/
sf::FloatRect const& fme::TextureVertices::getGlobalBounds()
{
	checkUpdateGlobalBounds();

	return m_globalBounds;
}

/*!
* \brief set the position of the left-top vertex of the global bounds
* \param the new position
*/
void fme::TextureVertices::setPosition(Vector2f const& newPosition)
{
	sf::Vector2f offset(
		newPosition.x - m_globalBounds.left,
		newPosition.y - m_globalBounds.top
		);

	sf::Transform transformation;
	transformation.translate(offset);
	applyTranformation(transformation);
}

void fme::TextureVertices::setSizeGlobalBounds(float width, float height)
{
	m_globalBounds.width = width;
	m_globalBounds.height = height;
}

void fme::TextureVertices::setColor(sf::Color const& color)
{
	sf::Vertex* vertices = getVerticesArray();

	for (unsigned int i = 0; i < m_size; i++)
	{
		vertices[i].color = color;
	}
}

/*!
* \brief calculate a translation on the sf::Tranform transformation
* \param offset the offset of the translation
* \param transformation the actual parameters of the final transformation
*			where the translation will be apply
*/
void fme::TextureVertices::translate(Vector2f const& offset, sf::Transform & transformation)
{
	transformation.translate(offset.x, offset.y);
}

/*!
* \brief calculate a rotation on the sf::Tranform transformation
* \param angleOfRotation in degree
* \param origin the origin of the rotation
* \param transformation the actual parameters of the final transformation
*			where the rotation will be apply
*/
void fme::TextureVertices::rotate(float angleOfRotation, Vector2f const& origin,
	sf::Transform & transformation)
{
	transformation.rotate(
		angleOfRotation,
		origin.x,
		origin.y
		);
}

/*!
* \brief apply the transformation on the m_vertices by calculating their
* \brief new position, and set the flag for the computing of the GlobalBounds
* \param transformation all parameters for the transformation calculated
*			before
*/
void fme::TextureVertices::applyTranformation(sf::Transform const& transformation)
{
	sf::Vertex* vertices = getVerticesArray();

	for (unsigned int i = 0; i < m_size; i++)
	{
		vertices[i].position = transformation.transformPoint(vertices[i].position);
	}

	m_globalBoundsUpToDate = false;
}

void fme::TextureVertices::setSizeArray(unsigned int newSize)
{
	m_size = newSize;
}

void fme::TextureVertices::checkUpdateGlobalBounds()
{
	if (!m_globalBoundsUpToDate)
	{
		computeGlobalBounds();
	}
}

void fme::TextureVertices::globalBoundsIsComputed()
{
	m_globalBoundsUpToDate = true;
}

bool fme::TextureVertices::isQuadVertices()
{
	return false;
}

bool fme::TextureVertices::isEmptyBoxVertices()
{
	return false;
}