#include "World.h"

World::World()
{

}


void World::gameLoop()
{
	Render rendering;
	InputHandler handler;

	char drawState = 'f';
	//f=freeform, c=circle, l=straight line, e=erase

	std::vector<GameActor> activeActors_;
	//activeActors_[0] = &thePlayer;

	double previous = gameClock.getElapsedTime().asMilliseconds();
	double lag = 0.0;
	while (rendering.window.isOpen())
	{
		double current = gameClock.getElapsedTime().asMilliseconds();
		double elapsed = current - previous;
		previous = current;
		lag += elapsed;

		handler.input(rendering);

		while (lag >= MS_PER_UPDATE)
		{
			//update();
			lag -= MS_PER_UPDATE;
		}

		rendering.renderCycle(lag / MS_PER_UPDATE, activeActors_);
	}
}