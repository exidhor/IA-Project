/*!
* \file Animation.hpp
* \brief A succession of texturesPoints linked
* \brief to a TileSet in a Sprite
* \author Exhidor
* \version 1.5
* \date 2016-02-01
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engines/GraphicEngine/TextureCharacteristics.hpp"
#include "Engines/GraphicEngine/Timer.hpp"
#include "Engines/GraphicEngine/Sprite.hpp"

namespace fme
{
	class Animation : public Sprite
	{
	public:
		Animation(TextureCharacteristics* animationCharacteristic,
			unsigned int layerLevel);
		Animation(Animation const& animation);
		~Animation();

		virtual void addToTileSet();

		// managing of the animation
		virtual bool actualize(double timeSpent);
		virtual void goToLine(unsigned int indexLine);
		virtual bool goToTheNextLine();

		//setters

		virtual void setRepeated(bool state);
		virtual void setContinueSequence(bool state);

		// state

		virtual void start();
		virtual void stop();
		virtual void restart();
		virtual void softRestart();

		// methods to provide a powerfull polymorphism

		virtual bool isAnimation();
		virtual bool isSprite();

	private:
		bool increaseAnimationIndex();
		void applyTextureOnVertices();

		Timer timer;
		unsigned int indexCulumn;
		unsigned int indexLine;

		//state

		bool isOn;
		bool repeated;
		bool continueSequence;
	};
}

