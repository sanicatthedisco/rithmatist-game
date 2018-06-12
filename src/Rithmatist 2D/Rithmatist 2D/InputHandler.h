#pragma once
#include <SFML/Graphics.hpp>
#include "GameActor.h"
#include "Render.h"

class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	void handleInput(sf::Event &event, char &drawState);
	void input(Render &rendering);
};