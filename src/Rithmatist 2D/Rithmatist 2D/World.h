#pragma once
#include <SFML/System.hpp>
#include <vector>
#include "Main.h"
#include "Render.h"
#include "InputHandler.h"

class World
{
public:
	World();
	void gameLoop();

	sf::Clock gameClock;
private:
	bool gameCycling = true;
	double previous = gameClock.getElapsedTime().asMilliseconds();
	double lag = 0.0;
	double MS_PER_UPDATE = 16.0;
};