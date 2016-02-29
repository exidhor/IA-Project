#include "Engines/PhysicEngine/Geometry/Size.hpp"

Size::Size()
	: Size(0, 0)
{
	// void
}

Size::Size(float width, float height)
{
	this->width = width;
	this->height = height;
}

Size::Size(Size const& size)
	: Size(size.width, size.height)
{
	// void
}