#include "Stroke.h"

Stroke::Stroke()
{
	type = 's';
	send = false;
	strength = 1000.0f;
}


Stroke::~Stroke()
{

}

void Stroke::draw(sf::RenderTarget& target)
{
	for (int i = 0; i < circles.size(); i++)
	{
		target.draw(circles[i]);
	}
}
