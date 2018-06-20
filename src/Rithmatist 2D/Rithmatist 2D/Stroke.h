#pragma once
#include <SFML/Graphics.hpp>
#include "GameActor.h"
#include <vector>
class Stroke : public GameActor
{
public:
	Stroke();
	~Stroke();
	void draw(sf::RenderTarget& target);

	std::vector<sf::CircleShape> circles;
};

