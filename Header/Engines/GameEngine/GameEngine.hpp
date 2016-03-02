#pragma once
#include <thread>
#include <chrono>
#include "Engines/GraphicEngine.hpp"
#include "Engines/PhysicEngine.hpp"

class GameEngine
{
public :
	GameEngine();
	~GameEngine();

	bool construct();

	void startGraphicEngine(float framePerSecond);

private :
	fme::GraphicEngine	m_graphicEngine;
	PhysicEngine		m_physicEngine;

	std::thread*		m_threadGraphic;
};