#include "Stroke.h"

Stroke::Stroke()
{
	circle.setRadius(2.0f);
}


Stroke::~Stroke()
{
}

void Stroke::draw(sf::RenderTarget& target)
{
	target.draw(circle);
}
