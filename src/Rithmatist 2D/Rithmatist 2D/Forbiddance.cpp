#include "Forbiddance.h"



Forbiddance::Forbiddance(std::vector<sf::Vector2f> data)
{
	regressionLine.setPrimitiveType(sf::LineStrip);
	//findSlope
	//findIntercept
	//find RMSD and convert to strength
	//Set up regressionLine VertexArray
}

Forbiddance::~Forbiddance()
{

}

void Forbiddance::draw(sf::RenderTarget& target)
{
	//Draw sf::line based on regression equation
	target.draw(regressionLine);
}

float Forbiddance::mean(std::vector<sf::Vector2f> values)
{
	//Find mean
	return 0.0f;
}

float Forbiddance::findSlope()
{
	//slope
	return 0.0f;
}

float Forbiddance::findIntercept()
{
	//Intercept
	return 0.0f;
}

float Forbiddance::findRMSD()
{
	//Calculate RMSD
	return 0.0f;
}
