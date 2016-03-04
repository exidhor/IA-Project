#include "Engines/GraphicEngine/TranslationTransformation.hpp"

fme::TranslationTransformation::TranslationTransformation()
	: m_timer(0)
{
	m_speedAbscissa = 0;
	m_speedOrdinate = 0;
	m_isDeterminedByTime = false;
}

void fme::TranslationTransformation::initAttribute(fme::QuadVertices* newQuadVertices)
{
	Transformation::initAttribute(newQuadVertices);
}

void fme::TranslationTransformation::initByTargetPoint(
	double timeUntilTheEnd, 
	Vector2f const& origin,
	Vector2f const& newTargetPoint)
{
	m_isDeterminedByTime = false;
	m_targetPoint = newTargetPoint;
	m_speedAbscissa = (m_targetPoint.x - origin.x) / (float)timeUntilTheEnd;
	m_speedOrdinate = (m_targetPoint.y - origin.y) / (float)timeUntilTheEnd;
}

void fme::TranslationTransformation::initBySpeed(
	double timeSpent, 
	Vector2f const& speedPerSecond)
{
	m_isDeterminedByTime = true;
	m_speedAbscissa = speedPerSecond.x;
	m_speedOrdinate = speedPerSecond.y;
	m_timer.setStartTime(timeSpent);
}

bool fme::TranslationTransformation::actualize(
	double timeSpent, 
	Vector2f & origin,
	sf::Transform & transformation)
{
	if (m_isOn)
	{
		bool isFinish = false;
		Vector2f deplacement;
		if (m_isDeterminedByTime)
		{
			if (m_timer.removeTime(timeSpent))
			{
				timeSpent += m_timer.getTimeLeft();
				stop();
				isFinish = true;
			}
			deplacement.x = m_speedAbscissa * (float)timeSpent;
			deplacement.y = m_speedOrdinate * (float)timeSpent;
		}
		else
		{
			bool XisArrived = false;
			bool YisArrived = false;
			deplacement.x = m_speedAbscissa * (float)timeSpent;
			deplacement.y = m_speedOrdinate * (float)timeSpent;

			if (m_speedAbscissa >= 0 && origin.x + deplacement.x >= m_targetPoint.x)
			{
				XisArrived = true;
			}
			else if (m_speedAbscissa <= 0 && origin.x + deplacement.x <= m_targetPoint.x)
			{
				XisArrived = true;
			}

			if (m_speedOrdinate >= 0 && origin.y + deplacement.y >= m_targetPoint.y)
			{
				YisArrived = true;
			}
			else if (m_speedOrdinate <= 0 && origin.y + deplacement.y <= m_targetPoint.y)
			{
				YisArrived = true;
			}

			if (XisArrived && YisArrived && !m_isInfinite)
			{
				deplacement.x = m_targetPoint.x - origin.x;
				deplacement.y = m_targetPoint.y - origin.y;
				stop();
				isFinish = true;
			}
		}
		origin.x += deplacement.x;
		origin.y += deplacement.y;
		
		m_quadVertices->translate(deplacement, transformation);
		m_quadVertices->applyTranformation(transformation);

		return isFinish;
	}

	return false;
}