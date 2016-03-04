#include "Engines/GraphicEngine/Sprite.hpp"

fme::Sprite::Sprite(TextureCharacteristics* textureCharacteristics,
					unsigned int layerLevel)
{
	// initialization of the Drawable part
	initTileSet(textureCharacteristics->getTileSet());
	setLayerLevel(layerLevel);
	QuadVertices* quadVertices = new QuadVertices(sf::FloatRect(textureCharacteristics->getTexturePoints(0, 0).x,
																textureCharacteristics->getTexturePoints(0, 0).y,
																textureCharacteristics->getTileSize(0).x,
																textureCharacteristics->getTileSize(0).y));
	initVertices(quadVertices);
	initOriginCenteredRelative(textureCharacteristics->getTileSize(0).x / 2,
								textureCharacteristics->getTileSize(0).y / 2);

	// initialization of the Sprite part
	m_textureCharacteristics = textureCharacteristics;

}

fme::Sprite::Sprite(fme::Sprite const& sprite)
	: Drawable(sprite)
{
	m_textureCharacteristics = sprite.m_textureCharacteristics;
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
	//Vector2f targetPointCentered(
	//	abscissa + m_quadVertices.getGlobalBounds().width / 2,
	//	ordinate + m_quadVertices.getGlobalBounds().height / 2
	//	);

	//m_translationManager.initByTargetPoint(
	//	timeUntilTheEnd,
	//	m_originCenteredRelative,
	//	targetPointCentered
	//	);
}

void fme::Sprite::setTranslationBySpeed(
	double timeUntilTheEnd, 
	unsigned int pixelPerSecondInAbsciss,
	unsigned int pixelPerSecondInOrdinate)
{
	m_translationManager.initBySpeed(
		timeUntilTheEnd,
		Vector2f(pixelPerSecondInAbsciss, pixelPerSecondInOrdinate)
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

/*!
* \brief give the type of the current object
* \return false because it's not a Shape
*/
bool fme::Sprite::isShape()
{
	return false;
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