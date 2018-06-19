#include "Stroke.h"

Stroke::Stroke()
{
	
}


Stroke::~Stroke()
{
}

void Stroke::draw(sf::RenderTarget& target)
{
	target.draw(rect);
}
