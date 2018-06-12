#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>
#include "GameActor.h"
class Stroke : public GameActor
{
public:
	Stroke();
	~Stroke();
	void draw(sf::RenderTarget& target);

	sf::VertexArray parts;
};

