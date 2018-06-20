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
	float mean(std::vector<float> values);
	void findSlope();
	void findIntercept();
	void findRMSD();

private:
	float m; //slope
	float b; //intercept
	float RMSD; //root mean squared deviation
	float strength;
	std::vector<sf::Vector2f> points; //input points
	std::vector<float> x; //x component of input
	std::vector<float> y; //y component of input
	sf::VertexArray regressionLine; //visualization of regression line y = mx + b
};

