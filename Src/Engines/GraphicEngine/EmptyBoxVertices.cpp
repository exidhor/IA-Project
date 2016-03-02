#include "Engines/GraphicEngine/EmptyBoxVertices.hpp"

fme::EmptyBoxVertices::EmptyBoxVertices(sf::FloatRect const& boxBounds)
	: TextureVertices(8)
{
	// coord
	float left	= boxBounds.left;
	float top	= boxBounds.top;
	float right = boxBounds.left + boxBounds.width;
	float bot	= boxBounds.top + boxBounds.height;

	// Points :
	sf::Vector2f leftTopPoint(left, top);
	sf::Vector2f rightTopPoint(right, top);
	sf::Vector2f rightBotPoint(right, bot);
	sf::Vector2f leftBotPoint(left, bot);

	// first line : left-top to right-top
	m_vertices[0] = sf::Vertex(leftTopPoint);
	m_vertices[1] = sf::Vertex(rightTopPoint);
	
	// second line : right-top to right-bot
	m_vertices[2] = sf::Vertex(rightTopPoint);
	m_vertices[3] = sf::Vertex(rightBotPoint);

	// third line : right-bot to left-bot
	m_vertices[4] = sf::Vertex(rightBotPoint);
	m_vertices[5] = sf::Vertex(leftBotPoint);

	// fourth line : left-bot to left-top
	m_vertices[6] = sf::Vertex(leftBotPoint);
	m_vertices[7] = sf::Vertex(leftTopPoint);

	computeGlobalBounds();
}

fme::EmptyBoxVertices::EmptyBoxVertices(TextureVertices const& textureVertices)
	: TextureVertices(textureVertices)
{
	for (unsigned int i = 0; i < 8; i++)
	{
		m_vertices[i] = textureVertices.getConstVerticesArray()[i];
	}
}

fme::EmptyBoxVertices::EmptyBoxVertices(EmptyBoxVertices const& emptyBoxVertices)
	: TextureVertices(emptyBoxVertices)
{
	for (unsigned int i = 0; i < 8; i++)
	{
		m_vertices[i] = emptyBoxVertices.m_vertices[i];
	}
}

fme::EmptyBoxVertices::~EmptyBoxVertices()
{
	delete[] m_vertices;
}

void fme::EmptyBoxVertices::setTexture(Vector2f const& newCoordTexture)
{
	// void because useless in this case
}

sf::Vertex* fme::EmptyBoxVertices::getVerticesArray()
{
	return m_vertices;
}

void fme::EmptyBoxVertices::computeGlobalBounds()
{
	float left = m_vertices[0].position.x;
	float right = m_vertices[0].position.x;

	float top = m_vertices[0].position.y;
	float bot = m_vertices[0].position.y;

	// step = 2
	for (unsigned int i = 1; i < 8; i += 2)
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

bool fme::EmptyBoxVertices::isEmptyBoxVertices()
{
	return true;
}

const sf::Vertex* fme::EmptyBoxVertices::getConstVerticesArray() const
{
	return m_vertices;
}