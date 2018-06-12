#pragma once
#include <SFML/Graphics.hpp>

class GameActor
{
public:
	virtual ~GameActor();
	virtual void draw(sf::RenderTarget& target);
};

