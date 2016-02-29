#include "Engines/PhysicEngine/Geometry/Point.hpp"

Point::Point()
	: Point(0, 0)
{
	// void
}

Point::Point(float abscissa, float ordinate)
{
	this->abscissa = abscissa;
	this->ordinate = ordinate;
}

Point::Point(Point const& point)
	: Point(point.abscissa, point.ordinate)
{
	// void
}