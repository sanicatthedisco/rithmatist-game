#include "Panel.h"

Panel::Panel()
{
	strength = 1000.0f;
}

Panel::Panel(std::string inTexFilePath, sf::Vector2f size, sf::Vector2f position)
{
	type = 'p';
	send = false;
	strength = 1000.0f;

	background.setSize(size);
	backTex.loadFromFile(inTexFilePath);
	background.setTexture(&backTex);
	background.setPosition(position);

	lastDrawState = 'n';
}

Panel::~Panel()
{

}

void Panel::draw(sf::RenderTarget & target)
{
	target.draw(background);
}

void Panel::update(InputHandler handler)
{
	if (handler.drawState != lastDrawState)
	{
		//std::cout << "Hey" << std::endl;
		switch(handler.drawState)
		{
		case 'n':
			backTex.loadFromFile("Textures/Frame.png");
			break;
		case 'e':
			backTex.loadFromFile("Textures/Erase.png");
			break;
		case 'f':
			backTex.loadFromFile("Textures/Forbiddance.png");
			break;
		case 'w':
			backTex.loadFromFile("Textures/Warding.png");
			break;
		case 'v':
			backTex.loadFromFile("Textures/Vigor.png");
			break;
		}
		background.setTexture(&backTex);
		lastDrawState = handler.drawState;
	}
}
