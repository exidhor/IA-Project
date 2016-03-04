#include "Utilities/Timer.hpp"

Timer::Timer(double newStartTime)
{
	m_startTime = newStartTime;
	m_timeLeft = m_startTime;
}

bool Timer::removeTime(double timeToRemove)
{
	m_timeLeft -= timeToRemove;
	if (m_timeLeft <= 0)
	{
		return true;
	}
	return false;
}

void Timer::restart(double newStartTime)
{
	m_timeLeft = newStartTime;
}

void Timer::setStartTime(double newStartTime)
{
	m_startTime = newStartTime;
	m_timeLeft = m_startTime;
}

double Timer::getStartTime() const
{
	return m_startTime;
}

void Timer::restart()
{
	m_timeLeft = m_startTime;
}

void Timer::softRestart()
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

double Timer::getTimeLeft()
{
	return m_timeLeft;
}