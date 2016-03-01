#include "Engines/GraphicEngine/Transformation.hpp"

fme::Transformation::Transformation()
{
	m_quadVertices = NULL;
	m_isInfinite = false;
	m_isOn = false;
}

fme::Transformation::~Transformation()
{
	//void
}

void fme::Transformation::initAttribute(fme::QuadVertices* newQuadVertices)
{
	m_quadVertices = newQuadVertices;
}

void fme::Transformation::start()
{
	m_isOn = true;
}

void fme::Transformation::stop()
{
	m_isOn = false;
}

void fme::Transformation::setIsInfinite(bool state)
{
	m_isInfinite = state;
}