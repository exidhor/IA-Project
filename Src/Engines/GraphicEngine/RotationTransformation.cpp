#include "Engines/GraphicEngine/RotationTransformation.hpp"

fme::RotationTransformation::RotationTransformation()
{
	m_finalAngle = 0;
	m_angleDegreeAdvancement = 0;
	m_speedPerSecond = 0;
}

fme::RotationTransformation::~RotationTransformation()
{
	//void
}

void fme::RotationTransformation::initAttribute(fme::QuadVertices* m_quadVertices)
{
	Transformation::initAttribute(m_quadVertices);
}


void fme::RotationTransformation::initRotateByTime(float newSpeedPerSecond, double timeUntilTheEnd)
{
	m_finalAngle = (float)(m_speedPerSecond * timeUntilTheEnd);
	m_speedPerSecond = newSpeedPerSecond;
}

void fme::RotationTransformation::initRotateByAngle(float newSpeedPerSecond, float newFinalAngle)
{
	if (newFinalAngle < 0)
	{
		int endRotation = -(int)newFinalAngle % 360;
		float floatPart = newFinalAngle - (int)newFinalAngle;
		int nbOfTurn = (int)(newFinalAngle / -360);
		newFinalAngle = nbOfTurn * 360 + endRotation + floatPart;
	}
	m_finalAngle = newFinalAngle;
	m_angleDegreeAdvancement = 0;
	m_speedPerSecond = newSpeedPerSecond;
}

bool fme::RotationTransformation::actualize(double timeSpent, Vector2f const& origin
	, sf::Transform & transformationPoint)
{
	if (m_isOn)
	{
		bool isFinish = false;
		float angleRotation = m_speedPerSecond * (float)timeSpent;

		m_angleDegreeAdvancement += angleRotation;
		if (m_speedPerSecond > 0 && m_angleDegreeAdvancement >= m_finalAngle)
		{
			isFinish = calculateEndOfRotation(angleRotation, true);
		}
		else if (m_speedPerSecond < 0 && m_angleDegreeAdvancement <= -m_finalAngle)
		{
			isFinish = calculateEndOfRotation(angleRotation, false);
		}

		m_quadVertices->rotate(angleRotation, origin, transformationPoint);
		m_quadVertices->applyTranformation(transformationPoint);

		return isFinish;
	}
	return false;
}

bool fme::RotationTransformation::calculateEndOfRotation(float & angleRotation, bool speedUpperThanZero)
{
	if (m_isInfinite)
	{
		if (speedUpperThanZero)
		{
			m_angleDegreeAdvancement -= m_finalAngle;
			m_angleDegreeAdvancement = 0;
		}
		else
		{
			m_angleDegreeAdvancement += m_finalAngle;
			m_angleDegreeAdvancement;
		}
		return false;
	}

	if (speedUpperThanZero)
	{
		angleRotation -= m_angleDegreeAdvancement - m_finalAngle;
	}
	else
	{
		angleRotation -= m_finalAngle - m_angleDegreeAdvancement;
	}
	m_isOn = false;

	return true;
}