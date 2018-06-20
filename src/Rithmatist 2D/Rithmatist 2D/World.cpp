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

	sf::RenderWindow *window = &rendering.window;

	double previous = gameClock.getElapsedTime().asMilliseconds();
	double lag = 0.0;
	while (rendering.window.isOpen())
	{
		double current = gameClock.getElapsedTime().asMilliseconds();
		double elapsed = current - previous;
		previous = current;
		lag += elapsed;

		handler.input(rendering); 

		//Fixed Time Loop
		while (lag >= MS_PER_UPDATE)
		{
			drawModePanel_->update(handler);
			handler.handleDraw(activeActors_, window);
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
	std::vector<GameActor*>().swap(activeActors_);
}