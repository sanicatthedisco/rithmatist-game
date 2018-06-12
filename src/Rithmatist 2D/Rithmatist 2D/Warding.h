#pragma once
#include "GameActor.h"
class Warding: public GameActor
{
public:
	Warding();
	~Warding();
	void draw(sf::RenderTarget& target);
};

