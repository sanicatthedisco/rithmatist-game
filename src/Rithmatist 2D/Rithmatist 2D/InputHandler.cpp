#include "InputHandler.h"

InputHandler::InputHandler()
{
	drawState = 'n';
	lastState = 'n';
	//f=freeform, c=circle, l=straight line, e=erase, n=none
	newDraw = false;
	endDraw = false;
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
			endDraw = true;
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
			currentStroke = new Stroke;
			currentStrokeIndex = activeActors_.size();
			activeActors_.push_back(currentStroke);
			newDraw = false;
		}
		sf::CircleShape currentCircle;
		currentCircle.setPosition(mousePos);
		currentCircle.setRadius(2.0f);
		currentStroke->circles.push_back(currentCircle);
	}
	if (drawState == 'n' && endDraw)
	{
		std::vector<sf::Vector2f> data;
		for (int i = 0; i < currentStroke->circles.size(); i++)
		{	
			data.push_back(currentStroke->circles[i].getPosition());
		}
		delete activeActors_[currentStrokeIndex];
		activeActors_[currentStrokeIndex] = new Forbiddance(data);
		endDraw = false;
	}
}
