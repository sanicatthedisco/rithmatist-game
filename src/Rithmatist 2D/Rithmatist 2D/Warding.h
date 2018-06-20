#pragma once
#include <SFML/Graphics.hpp>
#include <numeric>
#include <iostream>
#include "GameActor.h"

class Warding: public GameActor
{
public:
	Warding(std::vector<sf::Vector2f> data);
	~Warding();
	virtual void draw(sf::RenderTarget& target);
	float mean(std::vector<float> values);
	void CircularRegression();
	void CircleFitByTaubin();

private:
	sf::CircleShape regressionCircle;
	std::vector<sf::Vector2f> points; //input points
	std::vector<float> x; //x component of input
	std::vector<float> y; //y component of input
	float strength;
};


