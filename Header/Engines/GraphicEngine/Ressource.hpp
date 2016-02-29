#pragma once
#include "Engines/GraphicEngine/Sprite.hpp"

namespace fme
{
	class Ressource
	{
	public:
		Ressource(Sprite* sprite)
		{
			this->sprite = sprite;
			isUsed = false;
		}

		~Ressource()
		{
			//delete sprite;
		}

		Sprite* sprite;
		bool isUsed;
	};
}