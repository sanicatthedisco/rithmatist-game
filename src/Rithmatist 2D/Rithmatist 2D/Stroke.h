#pragma once
#include <SFML/Graphics.hpp>
#include "GameActor.h"
class Stroke : public GameActor
{
public:
	Stroke();
	~Stroke();
	void draw(sf::RenderTarget& target);

	sf::CircleShape circle;
};

