#include "GraphicEngine/Sprite.hpp"

fme::Sprite::Sprite(TextureCharacteristics* textureCharacteristics,
	unsigned int layerLevel)
	: quadVertices(
					sf::FloatRect(textureCharacteristics->getTexturePoints(0, 0).x,
								textureCharacteristics->getTexturePoints(0, 0).y,
									textureCharacteristics->getTileSize(0).x,
									textureCharacteristics->getTileSize(0).y
									)
					),
	originCenteredRelativedToTheWindow(
					textureCharacteristics->getTileSize(0).x / 2,
					textureCharacteristics->getTileSize(0).y / 2
	)
{
	translationTransformation.initAttribute(&quadVertices);
	rotationTransformation.initAttribute(&quadVertices);

	this->textureCharacteristics = textureCharacteristics;
	layerLevelOfDisplay = layerLevel;
	isHide = false;
}

fme::Sprite::Sprite(fme::Sprite const& sprite)
	:quadVertices(sprite.quadVertices),
	originCenteredRelativedToTheWindow(sprite.originCenteredRelativedToTheWindow),
	rotationTransformation(),
	translationTransformation()
{

	translationTransformation.initAttribute(&quadVertices);
	rotationTransformation.initAttribute(&quadVertices);

	layerLevelOfDisplay = sprite.layerLevelOfDisplay;
	textureCharacteristics = sprite.textureCharacteristics;
	isHide = false;
}

fme::Sprite::~Sprite()
{
	// void
}

// -------------- animations ---------------------------------

bool fme::Sprite::actualize(double timeSpent)
{
	sf::Transform transform2;

	translationTransformation.actualize(
		timeSpent,
		originCenteredRelativedToTheWindow,
		transform2
		);

	sf::Transform transform;

	rotationTransformation.actualize(
		timeSpent,
		originCenteredRelativedToTheWindow,
		transform
		);

	//quadVertices.applyTranformation(transform);

	return false;
}

void fme::Sprite::addToTileSet()
{
	if (!isHide)
	{
		this->quadVertices.addVerticesToTheTileSet(
			textureCharacteristics->getTileSet(),
			layerLevelOfDisplay
			);
	}
}

// -------------- getters ------------------------------------

fme::Vector2f fme::Sprite::getPosition()
{
	return quadVertices.getPosition();
}

fme::Vector2f fme::Sprite::getGlobalPosition()
{
	return quadVertices.getPosition();
}

fme::Vector2f fme::Sprite::getGlobalSize()
{
	return fme::Vector2f(quadVertices.getGlobalBounds().width,
		quadVertices.getGlobalBounds().height);
}

// -------------- setters ------------------------------------

void fme::Sprite::setPosition(float absciss, float ordinate)
{
	fme::Vector2f newOrigin(
		absciss + quadVertices.getGlobalBounds().width / 2,
		ordinate + quadVertices.getGlobalBounds().height / 2
	);

	fme::Vector2f offset(
		newOrigin.x - originCenteredRelativedToTheWindow.x,
		newOrigin.y - originCenteredRelativedToTheWindow.y
	);

	sf::Transform transform;
	this->quadVertices.translate(offset, transform);
	quadVertices.applyTranformation(transform);

	originCenteredRelativedToTheWindow = newOrigin;
}

void fme::Sprite::move(float offsetX, float offsetY)
{
	fme::Vector2f offset(
		offsetX,
		offsetY
		);

	sf::Transform transform;
	this->quadVertices.translate(offset, transform);
	quadVertices.applyTranformation(transform);

	originCenteredRelativedToTheWindow.x += offsetX;
	originCenteredRelativedToTheWindow.y += offsetY;
}

void fme::Sprite::setGlobalPosition(float absciss, float ordinate)
{
	quadVertices.setPosition(fme::Vector2f(absciss, ordinate));
}

void fme::Sprite::setLayerLevel(unsigned int layerLevel)
{
	layerLevelOfDisplay = layerLevel;
}

// -------------- transformation  ----------------------------

void fme::Sprite::setRotationByTime(float speedPerSecond, double timeUntilTheEnd)
{
	rotationTransformation.initRotateByTime(speedPerSecond, timeUntilTheEnd);
}

void fme::Sprite::setRotationByAngle(float speedPerSecond, float newFinalAngle)
{
	rotationTransformation.initRotateByAngle(speedPerSecond, newFinalAngle);
}

void fme::Sprite::setInfiniteRotation(bool state)
{
	rotationTransformation.setIsInfinite(state);
}

void fme::Sprite::startRotation()
{
	rotationTransformation.start();
}

void fme::Sprite::stopRotation()
{
	rotationTransformation.stop();
}

void fme::Sprite::setTranslationByTargetPoint(double timeUntilTheEnd,
	float absciss, float ordinate)
{
	fme::Vector2f targetPointCentered(
		absciss + quadVertices.getGlobalBounds().width / 2,
		ordinate + quadVertices.getGlobalBounds().height / 2
		);

	translationTransformation.initByTargetPoint(
		timeUntilTheEnd,
		originCenteredRelativedToTheWindow,
		targetPointCentered
		);
}

void fme::Sprite::setTranslationBySpeed(double timeUntilTheEnd, unsigned int pixelPerSecondInAbsciss,
	unsigned int pixelPerSecondInOrdinate)
{
	translationTransformation.initBySpeed(
		timeUntilTheEnd,
		fme::Vector2f(pixelPerSecondInAbsciss, pixelPerSecondInOrdinate)
		);
}

void fme::Sprite::startTranslation()
{
	translationTransformation.start();
}

void fme::Sprite::stopTranslation()
{
	translationTransformation.stop();
}

// -------------- state --------------------------------------

void fme::Sprite::hide()
{
	isHide = true;
}

void fme::Sprite::show()
{
	isHide = false;
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