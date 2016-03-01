#include <thread>
#include <chrono>
#include "Engines/GameEngine.hpp"

int main()
{
	GameEngine gameEngine;

	gameEngine.construct();

	gameEngine.startGraphicEngine(100);

	// freeze !!!!!!!!
	std::this_thread::sleep_for(std::chrono::hours(100));

	return 0;
}