#include "World.h"

World::World()
{

}


void World::gameLoop()
{
	Render rendering;
	InputHandler handler;

	std::vector<GameActor*> activeActors_;
	
	Panel *drawModePanel_ = new Panel("Textures/Frame.png", sf::Vector2f(64.0f, 64.0f), sf::Vector2f(0.0f, 0.0f));
	activeActors_.push_back(drawModePanel_);

	Panel *divider_ = new Panel();
	divider_->background.setSize(sf::Vector2f(1000.0f, 4.0f));
	divider_->background.setPosition(sf::Vector2f(0.0f, 498.0f));
	divider_->background.setFillColor(sf::Color(209, 161, 0));
	activeActors_.push_back(divider_);
	

	std::vector<Vigor*> activeVigors_;

	sf::RenderWindow *window = &rendering.window;
	bool m_keepM = false;

	double previous = gameClock.getElapsedTime().asMilliseconds();
	double lag = 0.0;
	while (rendering.window.isOpen())
	{
		double current = gameClock.getElapsedTime().asMilliseconds();
		double elapsed = current - previous;
		previous = current;
		lag += elapsed;

		handler.input(rendering, window);

		//Fixed Time Loop
		while (lag >= MS_PER_UPDATE)
		{
			//Keep mouse cursor in window
			/*if (m_keepM)
			{
				int maxX = window->getSize().x;
				int maxY = window->getSize().y;

				int mX = sf::Mouse::getPosition(*window).x;
				int mY = sf::Mouse::getPosition(*window).y;

				if (mX < 0 || mY < 0 || mX > maxX || mY > maxY)
				{
					if (mX < 0)
						mX = 0;
					else if (mX > maxX)
						mX = maxX;

					if (mY < -30)
						mY = -30;
					else if (mY > maxY)
						mY = maxY;

					sf::Mouse::setPosition(sf::Vector2i(mX, mY), *window);
				}
			}*/

			drawModePanel_->update(handler);
			handler.handleDraw(activeActors_, activeVigors_, window);
			//Update Vigors
			for (int i = 0; i < activeVigors_.size(); i++)
			{
				activeVigors_[i]->Visualize();
			}
			lag -= MS_PER_UPDATE;
		}

		rendering.renderCycle(lag / MS_PER_UPDATE, activeActors_);
	}

	/*for (int i = 0; i < activeActors_.size(); i++)
	{
		if (activeActors_[i])
		{
			delete activeActors_[i];
		}
	}*/
	std::vector<Vigor*>().swap(activeVigors_);
	std::vector<GameActor*>().swap(activeActors_);
}