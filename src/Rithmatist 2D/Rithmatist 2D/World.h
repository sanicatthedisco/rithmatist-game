#pragma once
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <iostream>
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
	std::vector<sf::Vector2f> extractPoints(sf::Packet& packet);
	//friend sf::Packet& operator<<(sf::Packet& packet, Forbiddance& forbiddance)
	//{
	//	std::cout << "Pack Forbid\n";
	//	packet << forbiddance.type;
	//	sf::Uint16 pointCount = forbiddance.x.size();
	//	packet << pointCount;

	//	for (int i = 0; i < forbiddance.x.size(); i++)
	//	{
	//		packet << forbiddance.x[i] << forbiddance.y[i];
	//	}

	//	return packet;
	//}



	bool gameCycling = true;
	double previous = gameClock.getElapsedTime().asMilliseconds();
	double lag = 0.0;
	const double MS_PER_UPDATE = 16.0;
	bool m_keepM;
};