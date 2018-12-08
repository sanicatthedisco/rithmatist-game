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

void InputHandler::input(Render& rendering, sf::RenderWindow *window)
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
			handleInput(event, window);
		}
	}
}

void InputHandler::handleInput(sf::Event &event, sf::RenderWindow *window)
{
	sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	if (event.type == sf::Event::KeyPressed)
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
	else if (mousePos.y > 502.0f)
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
			}
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			//std::cout << "SIRRR" << std::endl;
			if (event.key.code == sf::Mouse::Left && drawState != 'n')
			{
				//Draw end
				endDraw = true;
				isDrawing = false;
				std::cout << "End" << std::endl;
			}
			else if (event.key.code == sf::Mouse::Right)
			{
				//Erase end
				drawState = 'n';
				std::cout << "Erase end and state is " << drawState << std::endl;
			}
		}
	}
}

void InputHandler::handleDraw(std::vector<GameActor*> &activeActors_, std::vector<Vigor*> &activeVigors_, sf::RenderWindow *window)
{
	sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	if (drawState == 'n')
	{
		return;
	}
	else if (drawState == 'e')
	{
		// Erase
		for (int i = 0; i < activeActors_.size(); i++)
		{
			activeActors_[i]->erase(mousePos.x, mousePos.y);
		}
		return;
	}
	if (isDrawing)
	{
		if (mousePos.y > 502.0f)
		{
			if (newDraw)
			{
				currentStroke_ = new Stroke;
				currentStrokeIndex = std::find(activeActors_.begin(), activeActors_.end(), currentStroke_) - activeActors_.begin();
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
		currentStrokeIndex = std::find(activeActors_.begin(), activeActors_.end(), currentStroke_) - activeActors_.begin();
		if (currentStrokeIndex < activeActors_.size())
		{
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
				activeVigors_.push_back(new Vigor(data));
				activeActors_[currentStrokeIndex] = activeVigors_.back();
				break;
			}

			activeActors_[currentStrokeIndex]->send = true;
		}
		else
		{
			std::cout << "Failed to find Stroke in activeActors_" << std::endl;
		}
		
		endDraw = false;
	}
}
