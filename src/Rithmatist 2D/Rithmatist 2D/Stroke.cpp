#include "Stroke.h"

Stroke::Stroke()
{
	
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
