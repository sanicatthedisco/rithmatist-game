#include "Stroke.h"

Stroke::Stroke()
{
	parts.setPrimitiveType(sf::Quads);
}


Stroke::~Stroke()
{
}

void Stroke::draw(sf::RenderTarget& target)
{
	target.draw(parts);
}
