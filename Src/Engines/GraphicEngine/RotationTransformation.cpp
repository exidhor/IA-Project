#include "Engines/GraphicEngine/RotationTransformation.hpp"

fme::RotationTransformation::RotationTransformation()
{
	finalAngle = 0;
	angleDegreeAdvancement = 0;
}

fme::RotationTransformation::~RotationTransformation()
{
	//void
}

void fme::RotationTransformation::initAttribute(fme::QuadVertices* quadVertices)
{
	Transformation::initAttribute(quadVertices);
}


void fme::RotationTransformation::initRotateByTime(float newSpeedPerSecond, double timeUntilTheEnd)
{
	finalAngle = (float)(speedPerSecond * timeUntilTheEnd);
	speedPerSecond = newSpeedPerSecond;
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
	finalAngle = newFinalAngle;
	angleDegreeAdvancement = 0;
	speedPerSecond = newSpeedPerSecond;
}

bool fme::RotationTransformation::actualize(double timeSpent, fme::Vector2f const& origin
	, sf::Transform & transformationPoint)
{
	if (isOn)
	{
		bool isFinish = false;
		float angleRotation = speedPerSecond * (float)timeSpent;

		angleDegreeAdvancement += angleRotation;
		if (speedPerSecond > 0 && angleDegreeAdvancement >= finalAngle)
		{
			isFinish = calculateEndOfRotation(angleRotation, true);
		}
		else if (speedPerSecond < 0 && angleDegreeAdvancement <= -finalAngle)
		{
			isFinish = calculateEndOfRotation(angleRotation, false);
		}

		quadVertices->rotate(angleRotation, origin, transformationPoint);
		quadVertices->applyTranformation(transformationPoint);

		return isFinish;
	}
	return false;
}

bool fme::RotationTransformation::calculateEndOfRotation(float & angleRotation, bool speedUpperThanZero)
{
	if (isInfinite)
	{
		if (speedUpperThanZero)
		{
			angleDegreeAdvancement -= finalAngle;
			angleDegreeAdvancement = 0;
		}
		else
		{
			angleDegreeAdvancement += finalAngle;
			angleDegreeAdvancement;
		}
		return false;
	}

	if (speedUpperThanZero)
	{
		angleRotation -= angleDegreeAdvancement - finalAngle;
	}
	else
	{
		angleRotation -= finalAngle - angleDegreeAdvancement;
	}
	isOn = false;

	return true;
}