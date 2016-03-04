/*!
* \file		RectangleShape.hpp
* \brief	A empty rectangle simbolize by
*			stripped lines
* \author	Exhidor
* \version	0.1
* \date		2016-03-01
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engines/GraphicEngine/TextureCharacteristics.hpp"
#include "Utilities/Timer.hpp"
#include "Engines/GraphicEngine/Sprite.hpp"

namespace fme
{
	class RectangleShape
	{
	public:


	private:
		
		TextureCharacteristics* m_textureCharacteristics;
		sf::Color				m_color;
	};
}

