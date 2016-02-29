#include "Engines/PhysicEngine/CollisionBox.hpp"

CollisionBox::CollisionBox()
{
	// void 
}

bool CollisionBox::estEnCollision(CollisionBox const& collisionBox) const
{
	// TO DO
	return false;
}

bool CollisionBox::contientPoint(float abscissa, float ordinate) const
{
	// TO DO
	return false;
}

void CollisionBox::setPosition(float abscissa, float ordinate)
{
	rectangle.abscissa = abscissa;
	rectangle.ordinate = ordinate;
}

void CollisionBox::setPosition(Point const& point)
{
	setPosition(point.abscissa, point.ordinate);
}

void CollisionBox::setSize(float width, float height)
{
	rectangle.width = width;
	rectangle.height = height;
}

void CollisionBox::setSize(Size const& size)
{
	setSize(size.width, size.height);
}

Point CollisionBox::getPosition() const
{
	return Point(rectangle.abscissa, rectangle.height);
}

Size CollisionBox::getSize() const
{
	return Size(rectangle.width, rectangle.height);
}