#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameActor.h"

class Forbiddance: public GameActor
{
public:
	Forbiddance(std::vector<sf::Vector2f> data);
	~Forbiddance();
	void draw(sf::RenderTarget& target);
	float mean(std::vector<sf::Vector2f> values);
	float findSlope();
	float findIntercept();
	float findRMSD();
private:
	float m;
	float b;
	float strength;
	std::vector<sf::Vector2f> data;
	sf::VertexArray regressionLine;
};

