#include "Engines/GraphicEngine/TranslationTransformation.hpp"

fme::TranslationTransformation::TranslationTransformation()
	: timer(0)
{
	speedAbsciss = 0;
	speedOrdinate = 0;
	isDeterminedByTime = false;
}

void fme::TranslationTransformation::initAttribute(fme::QuadVertices* newQuadVertices)
{
	Transformation::initAttribute(newQuadVertices);
}

void fme::TranslationTransformation::initByTargetPoint(double timeUntilTheEnd, fme::Vector2f const& origin,
	fme::Vector2f const& newTargetPoint)
{
	isDeterminedByTime = false;
	targetPoint = newTargetPoint;
	speedAbsciss = (targetPoint.x - origin.x) / (float)timeUntilTheEnd;
	speedOrdinate = (targetPoint.y - origin.y) / (float)timeUntilTheEnd;
}

void fme::TranslationTransformation::initBySpeed(double timeSpent, fme::Vector2f const& speedPerSecond)
{
	isDeterminedByTime = true;
	speedAbsciss = speedPerSecond.x;
	speedOrdinate = speedPerSecond.y;
	timer.setStartTime(timeSpent);
}

bool fme::TranslationTransformation::actualize(double timeSpent, fme::Vector2f & origin,
	sf::Transform & transformation)
{
	if (isOn)
	{
		bool isFinish = false;
		fme::Vector2f deplacement;
		if (isDeterminedByTime)
		{
			if (timer.removeTime(timeSpent))
			{
				timeSpent += timer.getTimeLeft();
				stop();
				isFinish = true;
			}
			deplacement.x = speedAbsciss * (float)timeSpent;
			deplacement.y = speedOrdinate * (float)timeSpent;
		}
		else
		{
			bool XisArrived = false;
			bool YisArrived = false;
			deplacement.x = speedAbsciss * (float)timeSpent;
			deplacement.y = speedOrdinate * (float)timeSpent;

			if (speedAbsciss >= 0 && origin.x + deplacement.x >= targetPoint.x)
			{
				XisArrived = true;
			}
			else if (speedAbsciss <= 0 && origin.x + deplacement.x <= targetPoint.x)
			{
				XisArrived = true;
			}

			if (speedOrdinate >= 0 && origin.y + deplacement.y >= targetPoint.y)
			{
				YisArrived = true;
			}
			else if (speedOrdinate <= 0 && origin.y + deplacement.y <= targetPoint.y)
			{
				YisArrived = true;
			}

			if (XisArrived && YisArrived && !isInfinite)
			{
				deplacement.x = targetPoint.x - origin.x;
				deplacement.y = targetPoint.y - origin.y;
				stop();
				isFinish = true;
			}
		}
		origin.x += deplacement.x;
		origin.y += deplacement.y;
		
		quadVertices->translate(deplacement, transformation);
		quadVertices->applyTranformation(transformation);

		return isFinish;
	}

	return false;
}