/*!
* \file Sprite.hpp
* \brief A unique texture symbolize by a QuadVertices
* \brief It provides transformation like rotation
* \brief or translation
* \author Exhidor
* \version 1.5
* \date 2016-02-01
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engines/GraphicEngine/TextureCharacteristics.hpp"
#include "Engines/GraphicEngine/QuadVertices.hpp"
#include "Engines/GraphicEngine/RotationTransformation.hpp"
#include "Engines/GraphicEngine/TranslationTransformation.hpp"

namespace fme
{
	class Sprite
	{
	public:
		Sprite(TextureCharacteristics* textureCharacteristics,
			unsigned int layerLevel = 0);
		Sprite(Sprite const& sprite);

		virtual ~Sprite();

		virtual void addToTileSet();

		// method to provid a efficient polymorphism 
		virtual bool actualize(double timeSpent);

		// getters
		Vector2f getPosition();
		Vector2f getGlobalPosition();
		Vector2f getGlobalSize();

		//setters
		void setPosition(float abscissa, float ordinate);
		void move(float offsetX, float offsetY);
		void setGlobalPosition(float abscissa, float ordinate);
		void setLayerLevel(unsigned int Layerlevel);

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

		// state
		void hide();
		void show();

		// methods to provide a powerfull polymorphism
		virtual bool isAnimation();
		virtual bool isSprite();

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

		QuadVertices				m_quadVertices;
		Vector2f					m_originCenteredRelative;
		unsigned int				m_layerLevelOfDisplay;

		//transformation
		RotationTransformation		m_rotationManager;
		TranslationTransformation	m_translationManager;

		//state
		bool						m_isHide;
	};
}