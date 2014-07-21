#pragma once

#include "Input.h"
#include "Vector2f.h"

class Game
{
public:
	Game();
	~Game();
	void input(Input &input);
	void update();
	void render();
};

