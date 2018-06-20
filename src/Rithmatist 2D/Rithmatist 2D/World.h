#pragma once
#include <SFML/System.hpp>
#include <vector>
#include <string>
#include "Main.h"
#include "Render.h"
#include "InputHandler.h"
#include "Panel.h"

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
	const double MS_PER_UPDATE = 16.0;
};