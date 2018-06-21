#include "Panel.h"

Panel::Panel()
{

}

Panel::Panel(std::string inTexFilePath, sf::Vector2f size, sf::Vector2f position)
{
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
