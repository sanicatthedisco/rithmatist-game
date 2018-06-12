#include "World.h"

World::World()
{

}


void World::gameLoop()
{
	Render rendering;
	InputHandler handler;

	std::vector<GameActor*> activeActors_;
	//activeActors_[0] = &thePlayer;

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
			//update();
			lag -= MS_PER_UPDATE;
		}

		handler.handleDraw(activeActors_, window);
		rendering.renderCycle(lag / MS_PER_UPDATE, activeActors_);
	}
}