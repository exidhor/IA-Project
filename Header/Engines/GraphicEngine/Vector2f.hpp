#pragma once

namespace fme
{
	class Vector2f
	{
	public :
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