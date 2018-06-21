#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class GameActor
{
public:
	virtual ~GameActor();
	virtual void Kill(std::vector<GameActor*> activeActors_);
	virtual void draw(sf::RenderTarget& target);
	void Kill();
};

