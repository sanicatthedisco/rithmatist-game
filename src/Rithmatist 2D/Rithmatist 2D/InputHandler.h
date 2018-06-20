#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameActor.h"
#include "Render.h"
#include "Stroke.h"
#include "Forbiddance.h"

class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	void handleInput(sf::Event &event);
	void input(Render &rendering);
	void handleDraw(std::vector<GameActor*> &activeActors_, sf::RenderWindow *window);

private:
	char drawState;
	char lastState;
	bool newDraw;
	bool endDraw;
	size_t currentStrokeIndex;
	Stroke *currentStroke;
	sf::Vector2f lastMousePos;
};