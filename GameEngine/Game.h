#pragma once

#include "Mesh.h"
#include "Shader.h"

class Input;

class Game
{
public:
	Game();
	~Game();
	void input(Input &input);
	void update();
	void render();

private:
	Mesh mesh;
	Shader shader;
};

