#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>

class GameActor
{
public:
	virtual ~GameActor();
	virtual void Kill(std::vector<GameActor*> activeActors_);
	virtual void draw(sf::RenderTarget& target);
	virtual bool checkIntersect(float x0, float y0, float x1, float y1);
	virtual void erase(float x, float y);
	virtual void pack(sf::Packet& packet);

	float strength;
	char type;
	bool send;
};

