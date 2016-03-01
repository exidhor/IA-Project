#include "Engines/GraphicEngine/Sprite.hpp"

fme::Sprite::Sprite(TextureCharacteristics* textureCharacteristics,
	unsigned int layerLevel)
	: m_quadVertices(
					sf::FloatRect(textureCharacteristics->getTexturePoints(0, 0).x,
									textureCharacteristics->getTexturePoints(0, 0).y,
									textureCharacteristics->getTileSize(0).x,
									textureCharacteristics->getTileSize(0).y
									)
					),
	m_originCenteredRelative(
					textureCharacteristics->getTileSize(0).x / 2,
					textureCharacteristics->getTileSize(0).y / 2
	)
{
	m_translationManager.initAttribute(&m_quadVertices);
	m_rotationManager.initAttribute(&m_quadVertices);

	m_textureCharacteristics = textureCharacteristics;
	m_layerLevelOfDisplay = layerLevel;
	m_isHide = false;
}

fme::Sprite::Sprite(fme::Sprite const& sprite)
	:m_quadVertices(sprite.m_quadVertices),
	m_originCenteredRelative(sprite.m_originCenteredRelative),
	m_rotationManager(),
	m_translationManager()
{

	m_translationManager.initAttribute(&m_quadVertices);
	m_rotationManager.initAttribute(&m_quadVertices);

	m_layerLevelOfDisplay = sprite.m_layerLevelOfDisplay;
	m_textureCharacteristics = sprite.m_textureCharacteristics;
	m_isHide = false;
}

fme::Sprite::~Sprite()
{
	// void
}

// -------------- animations ---------------------------------

bool fme::Sprite::actualize(double timeSpent)
{
	/*
	sf::Transform transform2;

	m_translationManager.actualize(
		timeSpent,
		m_originCenteredRelative,
		transform2
		);

	sf::Transform transform;

	m_rotationManager.actualize(
		timeSpent,
		m_originCenteredRelative,
		transform
		);

		*/
	//m_quadVertices.applyTranformation(transform);

	return false;
}

void fme::Sprite::addToTileSet()
{
	if (!m_isHide)
	{
		this->m_quadVertices.addVerticesToTheTileSet(
			m_textureCharacteristics->getTileSet(),
			m_layerLevelOfDisplay
			);
	}
}

// -------------- getters ------------------------------------

fme::Vector2f fme::Sprite::getPosition()
{
	return m_quadVertices.getPosition();
}

fme::Vector2f fme::Sprite::getGlobalPosition()
{
	return m_quadVertices.getPosition();
}

fme::Vector2f fme::Sprite::getGlobalSize()
{
	return fme::Vector2f(m_quadVertices.getGlobalBounds().width,
		m_quadVertices.getGlobalBounds().height);
}

// -------------- setters ------------------------------------

void fme::Sprite::setPosition(float abscissa, float ordinate)
{
	fme::Vector2f newOrigin(
		abscissa + m_quadVertices.getGlobalBounds().width / 2,
		ordinate + m_quadVertices.getGlobalBounds().height / 2
	);

	fme::Vector2f offset(
		newOrigin.x - m_originCenteredRelative.x,
		newOrigin.y - m_originCenteredRelative.y
	);

	sf::Transform transform;
	this->m_quadVertices.translate(offset, transform);
	m_quadVertices.applyTranformation(transform);

	m_originCenteredRelative = newOrigin;
}

void fme::Sprite::move(float offsetX, float offsetY)
{
	fme::Vector2f offset(
		offsetX,
		offsetY
		);

	sf::Transform transform;
	this->m_quadVertices.translate(offset, transform);
	m_quadVertices.applyTranformation(transform);

	m_originCenteredRelative.x += offsetX;
	m_originCenteredRelative.y += offsetY;
}

void fme::Sprite::setGlobalPosition(float abscissa, float ordinate)
{
	m_quadVertices.setPosition(fme::Vector2f(abscissa, ordinate));
}

void fme::Sprite::setLayerLevel(unsigned int layerLevel)
{
	m_layerLevelOfDisplay = layerLevel;
}

// -------------- transformation  ----------------------------

void fme::Sprite::setRotationByTime(float speedPerSecond, double timeUntilTheEnd)
{
	m_rotationManager.initRotateByTime(speedPerSecond, timeUntilTheEnd);
}

void fme::Sprite::setRotationByAngle(float speedPerSecond, float newFinalAngle)
{
	m_rotationManager.initRotateByAngle(speedPerSecond, newFinalAngle);
}

void fme::Sprite::setInfiniteRotation(bool state)
{
	m_rotationManager.setIsInfinite(state);
}

void fme::Sprite::startRotation()
{
	m_rotationManager.start();
}

void fme::Sprite::stopRotation()
{
	m_rotationManager.stop();
}

void fme::Sprite::setTranslationByTargetPoint(
	double timeUntilTheEnd,
	float abscissa, 
	float ordinate)
{
	fme::Vector2f targetPointCentered(
		abscissa + m_quadVertices.getGlobalBounds().width / 2,
		ordinate + m_quadVertices.getGlobalBounds().height / 2
		);

	m_translationManager.initByTargetPoint(
		timeUntilTheEnd,
		m_originCenteredRelative,
		targetPointCentered
		);
}

void fme::Sprite::setTranslationBySpeed(
	double timeUntilTheEnd, 
	unsigned int pixelPerSecondInAbsciss,
	unsigned int pixelPerSecondInOrdinate)
{
	m_translationManager.initBySpeed(
		timeUntilTheEnd,
		fme::Vector2f(pixelPerSecondInAbsciss, pixelPerSecondInOrdinate)
		);
}

void fme::Sprite::startTranslation()
{
	m_translationManager.start();
}

void fme::Sprite::stopTranslation()
{
	m_translationManager.stop();
}

// -------------- state --------------------------------------

void fme::Sprite::hide()
{
	m_isHide = true;
}

void fme::Sprite::show()
{
	m_isHide = false;
}

// ------ methods to provide a powerfull polymorphism ------------

/*!
* \brief give the type of the current object
* \return false because it's not an Animation
*/
bool fme::Sprite::isAnimation()
{
	return false;
}

/*!
* \brief give the type of the current object
* \return true because it's a Sprite
*/
bool fme::Sprite::isSprite()
{
	return true;
}

// void method to use animation with polymorphism

void fme::Sprite::goToLine(unsigned int indexLine) {}
bool fme::Sprite::goToTheNextLine() { return false; }
void fme::Sprite::setRepeated(bool state) {}
void fme::Sprite::setContinueSequence(bool state) {}
void fme::Sprite::start() {}
void fme::Sprite::stop() {}
void fme::Sprite::restart() {}
void fme::Sprite::softRestart() {}