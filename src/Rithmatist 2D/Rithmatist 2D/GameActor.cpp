#include "GameActor.h"

GameActor::~GameActor()
{
	
}

void GameActor::Kill(std::vector<GameActor*> activeActors_)
{
	std::vector<GameActor*>::iterator it = std::find(activeActors_.begin(), activeActors_.end(), this);
	ptrdiff_t pos = it - activeActors_.begin();
	if (pos < activeActors_.size())
	{
		delete activeActors_[pos];
		activeActors_.erase(it);
	}
	else
	{
		std::cout << "Failed to find Stroke in activeActors_" << std::endl;
	}
}

void GameActor::draw(sf::RenderTarget& target)
{
}



