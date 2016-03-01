#include "Engines/GraphicEngine/Timer.hpp"

fme::Timer::Timer(double newStartTime)
{
	m_startTime = newStartTime;
	m_timeLeft = m_startTime;
}

bool fme::Timer::removeTime(double timeToRemove)
{
	m_timeLeft -= timeToRemove;
	if (m_timeLeft <= 0)
	{
		return true;
	}
	return false;
}

void fme::Timer::restart(double newStartTime)
{
	m_timeLeft = newStartTime;
}

void fme::Timer::setStartTime(double newStartTime)
{
	m_startTime = newStartTime;
	m_timeLeft = m_startTime;
}

double fme::Timer::getStartTime() const
{
	return m_startTime;
}

void fme::Timer::restart()
{
	m_timeLeft = m_startTime;
}

void fme::Timer::softRestart()
{
	m_timeLeft += m_startTime;
	//if m_startTime is bigger than m_timeLeft, it means that
	//the program is running slower than the animation, so we reset
	// the timeCounter "m_timeLeft"
	if (m_timeLeft <= 0)
	{
		m_timeLeft = m_startTime;
	}
}

double fme::Timer::getTimeLeft()
{
	return m_timeLeft;
}