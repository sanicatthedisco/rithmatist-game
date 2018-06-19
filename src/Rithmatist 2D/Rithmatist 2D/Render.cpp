#include "Render.h"



Render::Render()
{
	window.create(sf::VideoMode(900, 900), "Rithmatist 2D", sf::Style::Close | sf::Style::Titlebar);
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
}

void Render::renderCycle(double factor, std::vector<GameActor*> &activeActors_)
{
	//for (GameActors){} cycle array of active gameactors

	//for (int i = 0; i < numObjects; i++)
	//{
		//activeActors_[i]->actorSprite.setPosition(sf::Vector2f(factor*activeActors_[i]->horVel + activeActors_[i]->actorSprite.getPosition().x, factor*activeActors_[i]->vertVel + activeActors_[i]->actorSprite.getPosition().y));
	//}

	window.clear();

	//Draw

	//sf::Sprite sprite = activeActors[0]->actorSprite;
	//sf::Sprite sprite = activeActors_[0].actorSprite;
	//sprite.getPosition().x();
	//std::cout <<  << std::endl;
	//window.draw(thePlayer.actorSprite);
	//window.draw(activeActors[0].actorSprite);
	for (int i = 0; i <  activeActors_.size(); i++)
	{
		activeActors_[i]->draw(window);
	}

	window.display();
}