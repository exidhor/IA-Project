/*!
* \file Transformation.hpp
* \brief Abstract class to an eventual future
* \brief polymorphism
* \author Exhidor
* \version 0.1
* \date 2016-02-01
*/

#pragma once
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Time.hpp>
#include "Engines/GraphicEngine/QuadVertices.hpp"

namespace fme
{
	class Transformation
	{
	public:
		Transformation();
		virtual ~Transformation();

		void initAttribute(QuadVertices* quadVertices);

		virtual void start();

		void stop();

		void setIsInfinite(bool state);

	protected:
		bool isOn;
		bool isInfinite;
		QuadVertices* quadVertices;
	};
}