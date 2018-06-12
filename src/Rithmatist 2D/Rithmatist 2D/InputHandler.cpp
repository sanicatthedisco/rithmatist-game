#include "InputHandler.h"

InputHandler::InputHandler()
{
	drawState = 'n';
	//f=freeform, c=circle, l=straight line, e=erase, n=none
	firstSet = true;
}

InputHandler::~InputHandler()
{

}

void InputHandler::input(Render& rendering)
{
	//List of events
	sf::Event event;
	//each visual frame
	while (rendering.window.pollEvent(event))
	{
		//If x-button pressed, close the window
		if (event.type == sf::Event::Closed)
		{
			rendering.window.close();
		}
		//Resize
		/*else if (event.type == sf::Event::Resized)
		{
		sf::View gameView(sf::FloatRect(0, 0, 1120, 630));
		int w = event.size.width;
		int h = event.size.height;
		if (w >= h)
		{
		gameView.setViewport(sf::FloatRect((w-h)/(2*h), 0, w/h, 1));
		}
		else if (h > w)
		{
		gameView.setViewport(sf::FloatRect(0, (w-h)/(2*w), 1, h/w));
		}
		rendering.window.setView(gameView);
		} */
		else
		{
			handleInput(event);
		}
	}
}

void InputHandler::handleInput(sf::Event &event)
{
	bool lastDrawState = drawState;
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.key.code == sf::Mouse::Left)
		{
			//Draw start
			drawState = 'f';
		}
		else if (event.type == sf::Mouse::Right)
		{
			//Erase start
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.key.code == sf::Mouse::Left)
		{
			//Draw end
			drawState = 'n';
		}
		else if (event.type == sf::Mouse::Right)
		{
			//Erase end
		}
	}
	else if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::LShift)
		{
			//Straight line mode
		}
	}
	if (lastDrawState == drawState)
	{
		newState = false;
	}
	else
	{
		newState = true;
	}
}

void InputHandler::handleDraw(std::vector<GameActor*> &activeActors_, sf::RenderWindow *window)
{
	if (drawState == 'f')
	{
		if (newState)
		{
			currentStroke = new Stroke;
		}
		sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
		if (firstSet)
		{
			quad[0] = sf::Vector2f(mousePos.x - 1.0f, mousePos.y + 1.0f);
			quad[1] = sf::Vector2f(mousePos.x - 1.0f, mousePos.y - 1.0f);
			firstSet = false;
		}
		else
		{
			quad[2] = sf::Vector2f(mousePos.x + 1.0f, mousePos.y - 1.0f);
			quad[3] = sf::Vector2f(mousePos.x + 1.0f, mousePos.y + 1.0f);
			for (int i = 0; i < 4; i++)
			{
				currentStroke->parts.append(quad[i]);
			}
			activeActors_.push_back(currentStroke);
			//GameActor *current = activeActors_[activeActors_.size() - 1];
			firstSet = true;
		}
	}
}
