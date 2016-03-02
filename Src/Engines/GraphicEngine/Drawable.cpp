#include "Engines/GraphicEngine/Drawable.hpp"

fme::Drawable::Drawable()
{
	m_vertices = NULL;
	m_tileSet = NULL;
	
	m_layerLevelOfDisplay = 0;
	m_isHide = false;
}

fme::Drawable::Drawable(Drawable const& drawableObject)
{
	if (drawableObject.m_vertices->isEmptyBoxVertices())
	{
		m_vertices = new EmptyBoxVertices(*drawableObject.m_vertices);
	}

	if (drawableObject.m_vertices->isQuadVertices())
	{
		m_vertices = new QuadVertices(*drawableObject.m_vertices);
	}
	else
	{
		std::cerr << "Error while trying to copy a Drawable object : vertices group unknown";
	}

	m_tileSet = drawableObject.m_tileSet;
	m_layerLevelOfDisplay = drawableObject.m_layerLevelOfDisplay;
	m_originCenteredRelative = drawableObject.m_originCenteredRelative;
	m_isHide = false;
}

fme::Drawable::~Drawable()
{
	delete m_vertices;
}

void fme::Drawable::initTileSet(TileSet* tileSet)
{
	m_tileSet = tileSet;
}

void fme::Drawable::initVertices(TextureVertices* vertices)
{
	m_vertices = vertices;
}

void fme::Drawable::addToTileSet()
{
	if (!m_isHide)
	{
		m_vertices->addVerticesToTheTileSet(m_tileSet, m_layerLevelOfDisplay);
	}
}

fme::Vector2f fme::Drawable::getPosition()
{
	return m_vertices->getPosition();
}

fme::Vector2f fme::Drawable::getGlobalSize()
{
	return Vector2f(m_vertices->getGlobalBounds().width,
					m_vertices->getGlobalBounds().height);
}

void fme::Drawable::setPosition(fme::Vector2f const position)
{
	// TODO : a deplacer dans le PhysicEngine et enlever
	// la translation

	fme::Vector2f newOrigin(
		position.x + m_vertices->getGlobalBounds().width / 2,
		position.y + m_vertices->getGlobalBounds().height / 2
		);

	fme::Vector2f offset(
		newOrigin.x - m_originCenteredRelative.x,
		newOrigin.y - m_originCenteredRelative.y
		);

	sf::Transform transform;
	this->m_vertices->translate(offset, transform);
	m_vertices->applyTranformation(transform);

	m_originCenteredRelative = newOrigin;
}

void fme::Drawable::setPosition(float abscissa, float ordinate)
{
	setPosition(Vector2f(abscissa, ordinate));
}

void fme::Drawable::setTexture(Vector2f const& newCoordTexture)
{
	m_vertices->setTexture(newCoordTexture);
}

void fme::Drawable::setColor(sf::Color const& color)
{
	m_vertices->setColor(color);
}

void fme::Drawable::move(float offsetX, float offsetY)
{
	fme::Vector2f offset(
		offsetX,
		offsetY
		);

	sf::Transform transform;
	m_vertices->translate(offset, transform);
	m_vertices->applyTranformation(transform);

	m_originCenteredRelative.x += offsetX;
	m_originCenteredRelative.y += offsetY;
}

void fme::Drawable::setLayerLevel(unsigned int layerLevel)
{
	m_layerLevelOfDisplay = layerLevel;
}

void fme::Drawable::initOriginCenteredRelative(int abscissa, int ordinate)
{
	m_originCenteredRelative.x = abscissa;
	m_originCenteredRelative.y = ordinate;
}

// -------------- state --------------------------------------

void fme::Drawable::hide()
{
	m_isHide = true;
}

void fme::Drawable::show()
{
	m_isHide = false;
}