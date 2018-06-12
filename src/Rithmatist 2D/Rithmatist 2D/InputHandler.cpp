#include "InputHandler.h"

InputHandler::InputHandler()
{

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
	}
}

void InputHandler::handleInput(sf::Event &event, char &drawState)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.key.code == sf::Mouse::Left)
		{
			//Draw start
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
}
