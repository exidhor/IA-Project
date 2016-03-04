#include "Engines/GraphicEngine/Drawable.hpp"

/*!
* \brief	Construct a drawable object with
*           NULL value. It needs to be init
*			before use it.
*/
fme::Drawable::Drawable()
{
	m_vertices = NULL;
	m_tileSet = NULL;
	
	m_layerLevelOfDisplay = 0;
	m_isHidden = false;
}

/*!
* \brief	Copy a drawable object and
*           the same value for everything
*			except flag hide.
* \param	drawableObject : the model for
*			the copy.
*/
fme::Drawable::Drawable(Drawable const& drawableObject)
{
	// construct the good fme::TextureVertices
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

	// doesn't copy this value
	m_isHidden = false;
}

/*!
* \brief	Destruct the vertices array.
*/
fme::Drawable::~Drawable()
{
	delete m_vertices;
}

/*!
* \brief	Set the value of the tileSet.
*			Keep a reference.
*			tileSet : reference to the TileSet.
*/
void fme::Drawable::initTileSet(TileSet* tileSet)
{
	m_tileSet = tileSet;
}

/*!
* \brief	Set the value of the vertices array.
*           Keep a reference.
* \param	vertices : reference to the vertices array.
*/
void fme::Drawable::initVertices(TextureVertices* vertices)
{
	m_vertices = vertices;
}

/*!
* \brief	Initialize the origin value.
* \param	abscissa : the abscissa origin.
* \param	ordinate : the ordinate origin.
*/
void fme::Drawable::initOriginCenteredRelative(int abscissa, int ordinate)
{
	m_originCenteredRelative.x = abscissa;
	m_originCenteredRelative.y = ordinate;
}


/*!
* \brief	Add all vertices to the linked fme::TileSet
*           if the object is not hidden.
*/
void fme::Drawable::addToTileSet()
{
	if (!m_isHidden)
	{
		m_vertices->addVerticesToTheTileSet(m_tileSet, m_layerLevelOfDisplay);
	}
}

/*!
* \return	The position of the left top
*			point of the globalBounds.
*/
Vector2f fme::Drawable::getPosition()
{
	return m_vertices->getPosition();
}

/*!
* \return	The size of the globalBounds.
*/
Vector2f fme::Drawable::getGlobalSize()
{
	return Vector2f(m_vertices->getGlobalBounds().width,
					m_vertices->getGlobalBounds().height);
}

/*!
* \brief	Set the position of the object with
*           a translation.
*			Update the origin centered.
* \param	position : the new position
*/
void fme::Drawable::setPosition(Vector2f const position)
{
	// TODO : a deplacer dans le PhysicEngine et enlever
	// la translation

	Vector2f newOrigin(
		position.x + m_vertices->getGlobalBounds().width / 2,
		position.y + m_vertices->getGlobalBounds().height / 2
		);

	Vector2f offset(
		newOrigin.x - m_originCenteredRelative.x,
		newOrigin.y - m_originCenteredRelative.y
		);

	sf::Transform transform;
	this->m_vertices->translate(offset, transform);
	m_vertices->applyTranformation(transform);

	m_originCenteredRelative = newOrigin;
}

/*!
* \brief	Set the position of the object with
*           a translation.
*			Update the origin centered.
* \param	abscissa : the new abscissa
* \param	ordinate : the new ordinate
*/
void fme::Drawable::setPosition(float abscissa, float ordinate)
{
	setPosition(Vector2f(abscissa, ordinate));
}

/*!
* \brief	Set the texture with the coord
*			of the left top point of the 
*			globalBounds sprite.
* \param	coordTexture : the coord of the
*			left top point of the globalBounds sprite.
*/
void fme::Drawable::setTexture(Vector2f const& newCoordTexture)
{
	m_vertices->setTexture(newCoordTexture);
}

/*!
* \brief	Set the color of the object.
* \param	color : the of the object.
*/
void fme::Drawable::setColor(sf::Color const& color)
{
	m_vertices->setColor(color);
}

/*!
* \brief	Move the object with a translation.
*			Update the origin.
* \param	offsetX : the x composant of the 
*			movement vector.
* \param	offsetY	: the y composant of the 
*			movement vector.
*/
void fme::Drawable::move(float offsetX, float offsetY)
{
	Vector2f offset(
		offsetX,
		offsetY
		);

	sf::Transform transform;
	m_vertices->translate(offset, transform);
	m_vertices->applyTranformation(transform);

	m_originCenteredRelative.x += offsetX;
	m_originCenteredRelative.y += offsetY;
}

/*!
* \brief	Set the level of the layer of
*			display.
* \param	layelLevel : the level of the
*			layer of display.
*/
void fme::Drawable::setLayerLevel(unsigned int layerLevel)
{
	m_layerLevelOfDisplay = layerLevel;
}

// -------------- state --------------------------------------

/*!
* \brief	Hide the object.
*			The object is not add
*			to the TileSet anymore.
*/
void fme::Drawable::hide()
{
	m_isHidden = true;
}

/*!
* \brief	Show the object.
*			The object can now be add
*			to the TileSet.
*/
void fme::Drawable::show()
{
	m_isHidden = false;
}