#include "GraphicEngine/Timer.hpp"

fme::Timer::Timer(double newStartTime)
{
	startTime = newStartTime;
	timeLeft = startTime;
}

bool fme::Timer::removeTime(double timeToRemove)
{
	timeLeft -= timeToRemove;
	if (timeLeft <= 0)
	{
		return true;
	}
	return false;
}

void fme::Timer::restart(double newStartTime)
{
	timeLeft = newStartTime;
}

void fme::Timer::setStartTime(double newStartTime)
{
	startTime = newStartTime;
	timeLeft = startTime;
}

double fme::Timer::getStartTime() const
{
	return startTime;
}

void fme::Timer::restart()
{
	timeLeft = startTime;
}

void fme::Timer::softRestart()
{
	timeLeft += startTime;
	//if startTime is bigger than timeLeft, it means that
	//the program is running slower than the animation, so we reset
	// the timeCounter "timeLeft"
	if (timeLeft <= 0)
	{
		timeLeft = startTime;
	}
}

double fme::Timer::getTimeLeft()
{
	return timeLeft;
}