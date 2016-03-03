/*!
* \file		Ressource.hpp
* \brief	store a sprite and a flag
*			to know if it is being used
* \author	Exhidor
* \version	0.1
* \date		2016-02-01
*/


#pragma once
#include "Engines/GraphicEngine/Sprite.hpp"

namespace fme
{
	class Ressource
	{
	public:
		Ressource(Sprite* sprite)
		{
			this->sprite	= sprite;
			isUsed			= false;
		}

		~Ressource()
		{
			//delete sprite;
		}

		Sprite* sprite;
		bool	isUsed;
	};
}