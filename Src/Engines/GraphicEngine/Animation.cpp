#include "Engines/GraphicEngine/Animation.hpp"

/*!
* \brief	Construct an Animation from 
*           an TextureCharacteristics.
* \param	animationCharacteristics : all 
*			characteristics necessary to
*			build the animation.
* \param	layerLevel : the place order during
*			the draw.
*/
fme::Animation::Animation(fme::TextureCharacteristics* newTextureCharacteristics,
							unsigned int newLayerLevel)

: fme::Sprite(newTextureCharacteristics, newLayerLevel),

	m_timer(newTextureCharacteristics->getTimePerFrame(0))
{
	m_textureCharacteristics = newTextureCharacteristics;

	m_indexLine = 0;
	m_indexCulumn = 0;

	m_isOn = false;
	m_repeated = false;
	m_continueSequence = false;
}

/*!
* \brief	Copy an fme::Animation from an 
*			another fme::Animation.
* \param	animation the animation model.
*/
fme::Animation::Animation(Animation const& animation)
	: fme::Sprite(animation),
	m_timer(animation.m_timer.getStartTime())
{
	m_textureCharacteristics = animation.m_textureCharacteristics;

	m_indexLine = 0;
	m_indexCulumn = 0;
	m_isOn = false;
	m_repeated = false;
	m_continueSequence = false;
}

/*!
* \brief	Void destructor. 
*/
fme::Animation::~Animation()
{
	//animations.clear();
}

// -------------- animations ---------------------------------

/*!
* \brief	Update the animation fron timeSpend
*			change texture, if needed.
*			Stop animation if it's finished.
*			Update transformations if needed.
* \param	timeSpend time of the current turn loop.
* \return	true if the animation is finished.
*/
bool fme::Animation::actualize(double timeSpent)
{
	fme::Sprite::actualize(timeSpent);

	if (m_isOn)
	{
		if (m_timer.removeTime(timeSpent))
		{
			if (increaseAnimationIndex())
			{
				if (m_continueSequence)
				{
					if (goToTheNextLine())
					{
						restart();
						if (!m_repeated)
						{
							m_isOn = false;
						}
					}
					else
					{
						softRestart();
					}
				}
				else if (m_repeated)
				{
					softRestart();
				}
				else
				{
					restart();
					m_isOn = false;
				}
				return true;
			}
			m_timer.softRestart();
		}
	}
	return false;
}

/*!
* \brief	Change the current animation array,
* \param	indexLine the index of the line target,
*/
void fme::Animation::goToLine(unsigned int indexLine)
{
	m_indexLine = indexLine;
	restart();
}

/*!
* \brief	Change the animation array, 
*			and take the next.
*			It doesn't reset the index of 
*			the animation.
* \return	true if it returns to the first
*			line.
*/
bool fme::Animation::goToTheNextLine()
{
	m_indexLine++;
	if (m_indexLine >= m_textureCharacteristics->getCulumnSize())
	{
		m_indexLine = 0;
		return true;
	}
	return false;
}

/*!
* \brief	Update texture then add 
*			the 4 vertices to the TileSet.
*/
void fme::Animation::addToTileSet()
{
	applyTextureOnVertices();
	Drawable::addToTileSet();
}

/*!
* \brief	Incremented the index of animations.
* \return	true if the animation line is finished.
*/
bool fme::Animation::increaseAnimationIndex()
{
	m_indexCulumn++;
	if (m_indexCulumn >= m_textureCharacteristics->getLineSizeOf(m_indexLine))
	{
		return true;
	}
	return false;
}

/*!
* \brief	Set texture on the vertices.
*/
void fme::Animation::applyTextureOnVertices()
{
	setTexture(m_textureCharacteristics->getTexturePoints(m_indexCulumn, m_indexLine));
}

// -------------- setters ------------------------------------

/*!
* \brief	Set the statement of m_repeated.
* \param	state : if it's repeated.
*/
void fme::Animation::setRepeated(bool state)
{
	m_repeated = state;
}

/*!
* \brief	Allow the animation to enchain on
*			the next animation line.
* \param	state : if it's a sequence 
*			of animation lines.
*/
void fme::Animation::setContinueSequence(bool state)
{
	m_continueSequence = state;
}

// -------------- state --------------------------------------

/*!
* \brief	Start the animation.
*/
void fme::Animation::start()
{
	m_isOn = true;
}

/*!
* \brief	Stop the animation.
*/
void fme::Animation::stop()
{
	m_isOn = false;
}

/*!
* \brief	Set the animation index to 0.
*			Restart the timer of the animation.
*/
void fme::Animation::restart()
{
	m_indexCulumn = 0;
	m_timer.restart();
}

/*!
* \brief	Set the animation index to 0.
*			It doesn't restart the timer of the animation.
*/
void fme::Animation::softRestart()
{
	m_indexCulumn = 0;
	m_timer.softRestart();
}

// ------ methods to provide a powerfull polymorphism ------------

/*!
* \brief	Give the type of the current object.
* \return	true because it's an Animation.
*/
bool fme::Animation::isAnimation()
{
	return true;
}

/*!
* \brief	Give the type of the current object.
* \return	false because it's not a Sprite.
*/
bool fme::Animation::isSprite()
{
	return false;
}