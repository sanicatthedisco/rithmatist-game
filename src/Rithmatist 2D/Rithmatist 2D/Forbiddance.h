#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameActor.h"

class Forbiddance: public GameActor
{
public:
	Forbiddance(std::vector<sf::Vector2f> data);
	~Forbiddance();
	virtual void draw(sf::RenderTarget& target);
	void pack(sf::Packet& packet);
	bool checkIntersect(float x0, float y0, float x1, float y1);
	void erase(float x, float y);

private:
	float mean(std::vector<float> values);

	bool swap;

	bool findSlope();
	void findIntercept();
	void findRMSD();

	float m; //slope
	float b; //intercept
	float RMSD; //root mean squared deviation
	std::vector<sf::Vector2f> points; //input points
	std::vector<float> x; //x component of input
	std::vector<float> y; //y component of input

	sf::VertexArray regressionLine; //visualization of regression line y = mx + b
};

