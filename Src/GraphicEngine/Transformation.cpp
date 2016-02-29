#include "GraphicEngine/Transformation.hpp"

fme::Transformation::Transformation()
{
	quadVertices = NULL;
	isInfinite = false;
	isOn = false;
}

fme::Transformation::~Transformation()
{
	//void
}

void fme::Transformation::initAttribute(fme::QuadVertices* newQuadVertices)
{
	quadVertices = newQuadVertices;
}

void fme::Transformation::start()
{
	isOn = true;
}

void fme::Transformation::stop()
{
	isOn = false;
}

void fme::Transformation::setIsInfinite(bool state)
{
	isInfinite = state;
}