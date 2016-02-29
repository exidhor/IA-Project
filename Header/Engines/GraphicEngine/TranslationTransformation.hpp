/*!
* \file Transformation.hpp
* \brief Abstract class to an eventual future
* \brief polymorphism
* \author Exhidor
* \version 0.1
* \date 2016-02-01
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Time.hpp>
#include "Engines/GraphicEngine/Transformation.hpp"
#include "Engines/GraphicEngine/Timer.hpp"

namespace fme
{
	class TranslationTransformation : public Transformation
	{
	public:
		TranslationTransformation();

		void initAttribute(QuadVertices* quadVertices);
		void initByTargetPoint(double timeUntilTheEnd, Vector2f const& origin,
			Vector2f const& targetPoint);
		void initBySpeed(double timeUntilTheEnd, Vector2f const& speedPerSecond);

		bool actualize(double timeSpent, Vector2f & origin,
			sf::Transform & transformation);

	private:
		Timer timer;
		Vector2f targetPoint;
		float speedAbsciss;
		float speedOrdinate;
		bool isDeterminedByTime;
	};
}