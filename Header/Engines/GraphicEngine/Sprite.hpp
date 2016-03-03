/*!
* \file		Sprite.hpp
* \brief	A unique texture symbolize by a QuadVertices
*			It provides transformation like rotation
*			or translation
* \author	Exhidor
* \version	1.6
* \date		2016-02-01
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engines/GraphicEngine/TextureCharacteristics.hpp"
#include "Engines/GraphicEngine/QuadVertices.hpp"
#include "Engines/GraphicEngine/RotationTransformation.hpp"
#include "Engines/GraphicEngine/TranslationTransformation.hpp"
#include "Engines/GraphicEngine/Drawable.hpp"

namespace fme
{
	class Sprite : public Drawable
	{
	public:
		Sprite();
		Sprite(TextureCharacteristics* textureCharacteristics,
			unsigned int layerLevel = 0);
		Sprite(Sprite const& sprite);

		virtual ~Sprite();

		// method to provid a efficient polymorphism 
		virtual bool actualize(double timeSpent);

		// transformation
		void setRotationByTime(float speedPerSecond, double timeUntilTheEnd);
		void setRotationByAngle(float speedPerSecond, float newFinalAngle);
		void setInfiniteRotation(bool state);
		void startRotation();
		void stopRotation();

		void setTranslationByTargetPoint(
			double timeUntilTheEnd, 
			float abscissa,
			float ordinate);

		void setTranslationBySpeed(
			double timeUntilTheEnd, 
			unsigned int pixelPerSecondInAbsciss,
			unsigned int pixelPerSecondInOrdinate);

		void startTranslation();
		void stopTranslation();

		// methods to provide a powerfull polymorphism
		virtual bool isAnimation();
		virtual bool isSprite();
		virtual bool isShape();

		// void method to use animation with polymorphism
		virtual void goToLine(unsigned int indexLine);
		virtual bool goToTheNextLine();
		virtual void setRepeated(bool state);
		virtual void setContinueSequence(bool state);
		virtual void start();
		virtual void stop();
		virtual void restart();
		virtual void softRestart();


	protected:
		TextureCharacteristics*		m_textureCharacteristics;

		//transformation
		RotationTransformation		m_rotationManager;
		TranslationTransformation	m_translationManager;
	};
}