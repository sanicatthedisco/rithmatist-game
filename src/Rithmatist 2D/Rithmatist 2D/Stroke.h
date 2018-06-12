#pragma once
#include "GameActor.h"
class Stroke : public GameActor
{
public:
	Stroke();
	~Stroke();
	void draw(sf::RenderTarget& target);
};

