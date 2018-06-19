#include "InputHandler.h"

InputHandler::InputHandler()
{
	drawState = 'n';
	lastState = 'n';
	//f=freeform, c=circle, l=straight line, e=erase, n=none
	newDraw = false;
	drawPart1 = true;
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
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.key.code == sf::Mouse::Left)
		{
			//Draw start
			drawState = 'f';
			drawPart1 = true;
			newDraw = true;
			std::cout << "Start" << std::endl;
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
			std::cout << "End" << std::endl;
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

void InputHandler::handleDraw(std::vector<GameActor*> &activeActors_, sf::RenderWindow *window)
{
	sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	if (drawState == 'f')
	{
		if (newDraw)
		{
			lastMousePos = mousePos;
			newDraw = false;
			drawPart1 = false;
		}
		else
		{
			if (drawPart1)
			{
				drawPart1 = false;
			}
			else if (!drawPart1)
			{
				currentStroke = new Stroke;

				sf::Vector2f triangle = lastMousePos - mousePos;

				float length = std::sqrt(std::pow(triangle.x, 2.0f) + std::pow(triangle.y, 2.0f));
				float theta = std::atan2(triangle.y, triangle.x);

				currentStroke->rect.setSize(sf::Vector2f(length, 4.0f));
				currentStroke->rect.setOrigin(0, 2);
				currentStroke->rect.setPosition(lastMousePos);
				currentStroke->rect.setRotation((theta*180.0f) / 3.1415f);

				activeActors_.push_back(currentStroke);

				drawPart1 = true;
				lastMousePos = mousePos;
			}
		}
	}
}
