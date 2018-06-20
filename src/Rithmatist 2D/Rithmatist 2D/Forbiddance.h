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
	float mean(std::vector<float> values);
	void findSlope();
	void findIntercept();
	void findRMSD();
private:
	float m;
	float b;
	float RMSD;
	float strength;
	std::vector<sf::Vector2f> points;
	std::vector<float> x;
	std::vector<float> y;
	sf::VertexArray regressionLine;
};

