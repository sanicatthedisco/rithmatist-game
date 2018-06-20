#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "GameActor.h"
#include "InputHandler.h"

class Panel : public GameActor
{

public:
	Panel();
	Panel(std::string inTexFilePath, sf::Vector2f size, sf::Vector2f position);
	~Panel();
	virtual void draw(sf::RenderTarget& target);
	void update(InputHandler handler);

	sf::RectangleShape background;
	sf::Texture backTex;
	char lastDrawState;
};

