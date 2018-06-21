#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameActor.h"
#include "Render.h"
#include "Stroke.h"
#include "Forbiddance.h"
#include "Warding.h"
#include "Vigor.h"

class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	void handleInput(sf::Event &event, sf::RenderWindow *window);
	void input(Render &rendering, sf::RenderWindow *window);
	void handleDraw(std::vector<GameActor*> &activeActors_, std::vector<Vigor*> &activeVigors_, sf::RenderWindow *window);

	char drawState;

private:
	bool isDrawing;
	bool newDraw;
	bool endDraw;
	size_t  currentStrokeIndex;
	Stroke *currentStroke_;
	sf::Vector2f lastMousePos;
};