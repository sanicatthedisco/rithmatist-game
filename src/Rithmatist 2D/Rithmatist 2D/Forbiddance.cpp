#include "Forbiddance.h"



Forbiddance::Forbiddance(std::vector<sf::Vector2f> data)
{
	send = false;
	type = 'f';

	swap = false;

	regressionLine.setPrimitiveType(sf::LineStrip);
	points = data;
	for (int i = 0; i < points.size(); i++)
	{
		x.push_back(points[i].x);
		y.push_back(points[i].y);
	}

	if (std::hypot(x.back() - x[0], y.back() - y[0]) > 50.0f)
	{
		//findSlope
		if (findSlope())
		{
			//findIntercept
			findIntercept();

			findRMSD();

			if (swap)
			{
				x.swap(y);
				b = -b / m;
				m = 1.0f / m;
			}
		}
		//find RMSD and convert to strength
		
		//std::cout << "RMSD: " << RMSD << " Strength: " << strength << std::endl;
		//Set up regressionLine VertexArray
		regressionLine.append(sf::Vertex(sf::Vector2f(points[0].x, m*points[0].x + b)));
		regressionLine.append(sf::Vertex(sf::Vector2f(points.back().x, m*points.back().x + b)));

		//std::cout << regressionLine[0].position.x << std::endl;
	}
	else
	{
		//std::cout << "Failed to draw forbiddance (Too short)." << std::endl;
	}
}

Forbiddance::~Forbiddance()
{

}

void Forbiddance::draw(sf::RenderTarget& target)
{
	// Update transparency based on strength
	int alpha = 255 * strength / 150.0f;
	if (alpha != regressionLine[0].color.a)
	{
		if (alpha < 20)
		{
			alpha = 20;
		}
		for (int i = 0; i < regressionLine.getVertexCount(); i++)
		{
			regressionLine[i].color.a = alpha;
		}
	}
	//Draw sf::line based on regression equation
	target.draw(regressionLine);
}

void Forbiddance::pack(sf::Packet& packet)
{
	//std::cout << "Pack Forbid\n";
	packet << type;
	sf::Uint16 pointCount = x.size();
	packet << pointCount;

	for (int i = 0; i < x.size(); i++)
	{
		packet << x[i] << 1000.0f - y[i];
	}
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

bool Forbiddance::findSlope()
{
	if(abs((y.back() - y[0]) / (x.back() - x[0])) > 1.5f)
	{
		//std::cout << "Swap" << std::endl;
		x.swap(y);
		swap = true;
	}

	//slope
	float numerator = 0.0f;
	float denominator = 0.0f;
	for (int i = 0; i < points.size(); i++)
	{
		numerator += (x[i] - mean(x))*(y[i] - mean(y));
		denominator += (x[i] - mean(x))*(x[i] - mean(x));
	}
	
	m = numerator / denominator;

	//if (abs(m) > 20.0f) // Near Vertical
	//{
	//	m = (y[0] - y[points.size() - 1]) / (x[0] - x[points.size() - 1]);
	//	b = y[0] - m * x[0];

	//	//Find better way to FIND STRENGTH when near vertical
	//	RMSD = 12.345f;
	//	strength = 123.456f;
	//	return false;
	//}
	//std::cout << "m: " << m << std::endl;

	return true;
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

bool Forbiddance::checkIntersect(float x0, float y0, float x1, float y1)
{
	//Check intercept of two line segments
	size_t lineBack = regressionLine.getVertexCount() - 1;
	float x2 = regressionLine[0].position.x;
	float y2 = regressionLine[0].position.y;
	float x3 = regressionLine[lineBack].position.x;
	float y3 = regressionLine[lineBack].position.y;

	// Check if both endpoints of l1 are on different sides of l2, 
	// and both endpoints of l2 are on opposite sides of l1
	return (((x2 - x0)*(y1 - y0) - (y2 - y0)*(x1 - x0))
		    * ((x3 - x0)*(y1 - y0) - (y3 - y0)*(x1 - x0)) < 0)
		   &&
		   (((x0 - x2)*(y3 - y2) - (y0 - y2)*(x3 - x2))
		    * ((x1 - x2)*(y3 - y2) - (y1 - y2)*(x3 - x2)) < 0);
}

void Forbiddance::erase(float x_, float y_)
{
	// Find dist b/w point of erase and line segment
	float x1 = x.front();
	float x2 = x.back();
	float y1 = y.front();
	float y2 = y.back();

	float A = x_ - x1;
	float B = y_ - y1;
	float C = x2 - x1;
	float D = y2 - y1;

	float dot = A * C + B * D;
	float len_sq = C * C + D * D;
	float param = -1;
	if (len_sq != 0) //in case of 0 length line
		param = dot / len_sq;

	float xx, yy;

	if (param < 0) {
		xx = x1;
		yy = y1;
	}
	else if (param > 1) {
		xx = x2;
		yy = y2;
	}
	else {
		xx = x1 + param * C;
		yy = y1 + param * D;
	}

	float dx = x_ - xx;
	float dy = y_ - yy;
	float dist = sqrt(dx * dx + dy * dy);

	//Kill if dist is less than five
	if (dist < 5.0f)
	{
		strength = 0.0f;
	}
}
