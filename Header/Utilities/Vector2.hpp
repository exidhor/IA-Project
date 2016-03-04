/*!
* \file		Vector2f.hpp
* \brief	store 2 floats
* \author	Exhidor
* \version	0.1
* \date		2016-02-10
*/

#pragma once

#define Vector2f Vector2<float>
#define Vector2i Vector2<int>
#define Vector2u Vector2<unsigned int>
#define Vector2d Vector2<double>
#define Vector2l Vector2<long>

template < typename T >
class Vector2
{
public :

	/*!
	* \brief initialize with (0,0) values
	*/
	Vector2()
	{
		this->x = 0;
		this->y = 0;
	}

	Vector2(T x, T y)
	{
		this->x = x;
		this->y = y;
	}

	template < typename U >
	Vector2(Vector2<U> const& vector2)
	{
		x = (T)vector2.x;
		y = (T)vector2.y;
	}

	T x;
	T y;
};