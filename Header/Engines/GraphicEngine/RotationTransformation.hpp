/*!
* \file		RotationTransformation.hpp
* \brief	[DEPRECATED] manage a rotation 
*			with a Timer or an angle
* \author	Exhidor
* \version	2.0
* \date		2016-02-01
*/

#pragma once
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Time.hpp>
#include "Engines/GraphicEngine/Transformation.hpp"

namespace fme
{
	class RotationTransformation : public Transformation
	{
	public:
		RotationTransformation();
		~RotationTransformation();

		void initAttribute(QuadVertices* quadVertices);

		void initRotateByTime(float speedPerSecond, double timeUntilTheEnd);
		void initRotateByAngle(float speedPerSecond, float finalAngle);

		bool actualize(double timeSpent, Vector2f const& origin,
			sf::Transform & transformationPoint);

	private:
		bool	calculateEndOfRotation(float & angleRotation, bool speedUpperThanZero);

		float	m_speedPerSecond;
		float	m_finalAngle;
		float	m_angleDegreeAdvancement;
	};
}