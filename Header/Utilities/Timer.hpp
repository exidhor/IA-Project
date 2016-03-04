/*!
* \file		Timer.hpp
* \brief	Used to time time spent.
*			It decrements and reset with the time passed
*			during the construction.
* \author	Exhidor
* \version	0.1
* \date		2016-02-01
*/

#pragma once
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Time.hpp>

class Timer
{
public:
	Timer(double startTime);
	bool	removeTime(double timeToRemove); //return true if it reach 0
	void	restart(double newStartTime); // restart with the newTime for timeDisplay
	void	restart(); //restart with the actual timeDisplay
	void	softRestart(); //restart with substracting the old timeLeft

	void	setStartTime(double newStartTime);
	double	getStartTime() const;
	double	getTimeLeft();

private:
	double m_startTime;
	double m_timeLeft;
};