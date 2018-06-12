#pragma once
#include <SFML/Graphics.hpp>
#include "GameActor.h"
#include <vector>
#include <iostream>

class Render
{
public:
	Render();
	void renderCycle(double factor, std::vector<GameActor*> &activeActors_);
	sf::RenderWindow window;
};