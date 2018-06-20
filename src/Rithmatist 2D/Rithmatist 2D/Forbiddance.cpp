#include "Forbiddance.h"



Forbiddance::Forbiddance(std::vector<sf::Vector2f> data)
{
	regressionLine.setPrimitiveType(sf::LineStrip);
	points = data;
	for (int i = 0; i < points.size(); i++)
	{
		x.push_back(points[i].x);
		y.push_back(points[i].y);
	}
	//findSlope
	findSlope();
	//findIntercept
	findIntercept();
	//find RMSD and convert to strength
	findRMSD();
	std::cout << "RMSD: " << RMSD << " Strength: " << strength << std::endl;
	//Set up regressionLine VertexArray
	regressionLine.append(sf::Vertex(sf::Vector2f(points[0].x, m*points[0].x + b)));
	regressionLine.append(sf::Vertex(sf::Vector2f(points.back().x, m*points.back().x + b)));
}

Forbiddance::~Forbiddance()
{

}

void Forbiddance::draw(sf::RenderTarget& target)
{
	//Draw sf::line based on regression equation
	target.draw(regressionLine);
}

float Forbiddance::mean(std::vector<float> values)
{
	//Find mean
	float sum = 0.0f;
	for (int i = 0; i < values.size(); i++)
	{
		sum += values[i];
	}
	return sum / values.size();
}

void Forbiddance::findSlope()
{
	//slope
	float numerator = 0.0f;
	float denominator = 0.0f;
	for (int i = 0; i < points.size(); i++)
	{
		numerator += (x[i] - mean(x))*(y[i] - mean(y));
		denominator += (x[i] - mean(x))*(x[i] - mean(x));
	}
	m = numerator / denominator;
}

void Forbiddance::findIntercept()
{
	//Intercept
	b = mean(y) - m * mean(x);
}

void Forbiddance::findRMSD()
{
	//Calculate RMSD
	float sumY = 0.0f; //Sum of Predicted y values - input y values
	for (int i = 0; i < points.size(); i++)
	{
		sumY += std::pow(m*x[i] + b - y[i], 2.0f);
	}
	RMSD = std::sqrt(sumY / points.size());

	//Strength
	if (RMSD > 20.0f)
	{
		//fail to draw
		strength = 0.0f;
	}
	else if (RMSD < 1.0f)
	{
		//max strength
		strength = 150.0f;
	}
	else if (RMSD >= 1.0f && RMSD <= 20.0f)
	{
		//Interpret (temp)
		strength = 150.0f / std::sqrt(RMSD);
	}
	else // ie NaN
	{
		//fail to draw 
		strength = 0.0f;
	}
}
