/*!
* \file		Vector2f.hpp
* \brief	store 2 floats
* \author	Exhidor
* \version	0.1
* \date		2016-02-10
*/

#pragma once

namespace fme
{
	class Vector2f
	{
	public :

		/*!
		* \brief initialize with (0,0) values
		*/
		Vector2f()
		{
			this->x = 0;
			this->y = 0;
		}

		Vector2f(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		float x;
		float y;
	};
}