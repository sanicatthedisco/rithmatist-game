#include "InputHandler.h"

InputHandler::InputHandler()
{
	drawState = 'n';
	//f=forbiddence, w=warding, v=vigor, e=erase, n=none
	isDrawing = false;
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
		if (event.key.code == sf::Mouse::Left && drawState != 'n')
		{
			//Draw start
			newDraw = true;
			isDrawing = true;
			std::cout << "Start" << std::endl;
		}
		else if (event.key.code == sf::Mouse::Right)
		{
			//Erase start
			drawState = 'e';
			isDrawing = true;
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.key.code == sf::Mouse::Left && drawState != 'n')
		{
			//Draw end
			endDraw = true;
			isDrawing = false;
			std::cout << "End" << std::endl;
		}
		else if (event.type == sf::Mouse::Right)
		{
			//Erase end
			isDrawing = false;
		}
	}
	else if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::W)
		{
			drawState = 'w';
		}
		if (event.key.code == sf::Keyboard::V)
		{
			drawState = 'v';
		}
		if (event.key.code == sf::Keyboard::F)
		{
			drawState = 'f';
		}
	}
}

void InputHandler::handleDraw(std::vector<GameActor*> &activeActors_, sf::RenderWindow *window)
{
	if (drawState == 'n')
	{
		return;
	}
	if (isDrawing)
	{
		if (drawState == 'e')
		{

		}
		else
		{
			sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
			if (newDraw)
			{
				currentStroke_ = new Stroke;
				currentStrokeIndex = activeActors_.size();
				activeActors_.push_back(currentStroke_);
				newDraw = false;
			}
			sf::CircleShape currentCircle;
			currentCircle.setPosition(mousePos);
			currentCircle.setRadius(2.0f);
			currentStroke_->circles.push_back(currentCircle);
		}
	}
	if (endDraw)
	{
		//Copy data points
		std::vector<sf::Vector2f> data;
		for (int i = 0; i < currentStroke_->circles.size(); i++)
		{
			data.push_back(currentStroke_->circles[i].getPosition());
		}
		//Clear stroke
		delete activeActors_[currentStrokeIndex];

		switch (drawState)
		{
		case 'f':
			activeActors_[currentStrokeIndex] = new Forbiddance(data);
			break;
		case 'w':
			activeActors_[currentStrokeIndex] = new Warding(data);
			break;
		case 'v':
			//activeActors_[currentStrokeIndex] = new Vigor(data);
			break;
		}
		
		endDraw = false;
	}
}
