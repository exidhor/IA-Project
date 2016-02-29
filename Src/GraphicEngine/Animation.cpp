#include "GraphicEngine/Animation.hpp"

/*!
* \brief Construct an Animation from an TextureCharacteristics
* \param animationCharacteristic all characteristics necessary to build the animation
*/
fme::Animation::Animation(fme::TextureCharacteristics* newTextureCharacteristics,
							unsigned int newLayerLevel)

: fme::Sprite(newTextureCharacteristics, newLayerLevel),

	timer(newTextureCharacteristics->getTimePerFrame(0))
{
	textureCharacteristics = newTextureCharacteristics;

	indexLine = 0;
	indexCulumn = 0;

	isOn = false;
	repeated = false;
	continueSequence = false;
}

/*!
* \brief Copy an fme::Animation from an another fme::Animation
* \param animation the animation model
*/
fme::Animation::Animation(Animation const& animation)
	: fme::Sprite(animation),
	timer(animation.timer.getStartTime())
{
	textureCharacteristics = animation.textureCharacteristics;

	indexLine = 0;
	indexCulumn = 0;
	isOn = false;
	repeated = false;
	continueSequence = false;
}

/*!
* \brief Destructor 
*/
fme::Animation::~Animation()
{
	//animations.clear();
}

// -------------- animations ---------------------------------

/*!
* \brief update the animation fron timeSpend
* \brief change texture, if needed
* \brief stop animation if it's finished
* \brief update transformations if needed
* \param timeSpend time of the current turn loop
* \return true if the animation is finished
*/
bool fme::Animation::actualize(double timeSpent)
{
	fme::Sprite::actualize(timeSpent);

	if (isOn)
	{
		if (timer.removeTime(timeSpent))
		{
			if (increaseAnimationIndex())
			{
				if (continueSequence)
				{
					if (goToTheNextLine())
					{
						restart();
						if (!repeated)
						{
							isOn = false;
						}
					}
					else
					{
						softRestart();
					}
				}
				else if (repeated)
				{
					softRestart();
				}
				else
				{
					restart();
					isOn = false;
				}
				return true;
			}
			timer.softRestart();
		}
	}
	return false;
}

/*!
* \brief change the current animation array
* \param indexLine the index of the line target
*/
void fme::Animation::goToLine(unsigned int indexLine)
{
	this->indexLine = indexLine;
	restart();
}

/*!
* \brief change the animation array, and take the next
* \brief it doesn't reset the index of the animation
*/
bool fme::Animation::goToTheNextLine()
{
	indexLine++;
	if (indexLine >= textureCharacteristics->getCulumnSize())
	{
		indexLine = 0;
		return true;
	}
	return false;
}

/*!
* \brief add the 4 vertices to the TileSet
*/
void fme::Animation::addToTileSet()
{
	if (!isHide)
	{
		applyTextureOnVertices();
		this->quadVertices.addVerticesToTheTileSet(
				textureCharacteristics->getTileSet(),
				layerLevelOfDisplay
			);
	}
}

/*!
* \brief incremented the index of animations
* \return true if the animation line is finished
*/
bool fme::Animation::increaseAnimationIndex()
{
	indexCulumn++;
	if (indexCulumn >= textureCharacteristics->getLineSizeOf(indexLine))
	{
		return true;
	}
	return false;
}

/*!
* \brief set texture on the vertices
*/
void fme::Animation::applyTextureOnVertices()
{
	this->quadVertices.setTexture(textureCharacteristics->getTexturePoints(indexCulumn, indexLine));
}

// -------------- setters ------------------------------------

/*!
* \brief set the statement of repeated
* \param the statement : if it's repeated
*/
void fme::Animation::setRepeated(bool state)
{
	repeated = state;
}

/*!
* \brief allow the animation to enchain on the next animation line
* \param the statement : if it's a sequence of animation lines
*/
void fme::Animation::setContinueSequence(bool state)
{
	continueSequence = state;
}

// -------------- state --------------------------------------

/*!
* \brief start the animation
*/
void fme::Animation::start()
{
	isOn = true;
}

/*!
* \brief stop the animation
*/
void fme::Animation::stop()
{
	isOn = false;
}

/*!
* \brief set the animation index to 0
* \brief restart the timer of the animation
*/
void fme::Animation::restart()
{
	indexCulumn = 0;
	timer.restart();
}

/*!
* \brief set the animation index to 0
* \brief don't restart the timer of the animation
*/
void fme::Animation::softRestart()
{
	indexCulumn = 0;
	timer.softRestart();
}

// ------ methods to provide a powerfull polymorphism ------------

/*!
* \brief give the type of the current object
* \return true because it's an Animation
*/
bool fme::Animation::isAnimation()
{
	return true;
}

/*!
* \brief give the type of the current object
* \return false because it's not a Sprite
*/
bool fme::Animation::isSprite()
{
	return false;
}