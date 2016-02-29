#include "Engines/PhysicEngine/Geometry/Rectangle.hpp"

Rectangle::Rectangle()
	: Rectangle(0, 0, 0, 0)
{
	// void
}

Rectangle::Rectangle(Size const& size)
	: Rectangle(0, 0, size.width, size.height)
{
	// void
}

Rectangle::Rectangle(Point const& position, Size const& size)
	: Rectangle(position.abscissa, position.ordinate, 
	size.width, size.height)
{
	// void
}

Rectangle::Rectangle(float abscissa, float ordinate, float width, float height)
{
	this->abscissa = abscissa;
	this->ordinate = ordinate;
	this->width = width;
	this->height = height;
}