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
	void pack(sf::Packet& packet);
	bool checkIntersect(float x0, float y0, float x1, float y1);
	float mean(std::vector<float> values);
	bool CircularRegression();
	bool CircleFitByTaubin();
	void erase(float x, float y);

private:
	sf::CircleShape regressionCircle;
	std::vector<sf::Vector2f> points; //input points
	std::vector<float> x; //x component of input
	std::vector<float> y; //y component of input

};


