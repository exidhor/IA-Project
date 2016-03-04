/*!
* \file		TilesCharacteristics.hpp
*			Configuration of an animation line or just a texture.
*			It store texture points, tile size and
*			time per frame.
* \author	Exhidor
* \version	1.0
* \date		2016-02-01
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utilities/Vector2.hpp"

namespace fme
{
	class TilesCharacteristics
	{
	public:
		TilesCharacteristics(
			Vector2f const& tileSize,
			std::vector <Vector2f> texturePoints,
			double timePerFrame);

		TilesCharacteristics(
			Vector2f const& tileSize,
			Vector2f const& oneTexturePoint);

		~TilesCharacteristics();

		Vector2f const& getTileSize();
		Vector2f const& getTexturePoints(unsigned int index);
		unsigned int	getArraySize();
		double			getTimePerFrame();

	private:
		Vector2f				m_tileSize;
		std::vector <Vector2f>	m_texturePoints;
		double					m_timePerFrame;
	};
}