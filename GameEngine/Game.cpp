#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::input(Input &input)
{
	if (input.getKeyDown(VK_UP))
		OutputDebugString("We've just pressed up!\n");
	if (input.getKeyUp(VK_UP))
		OutputDebugString("We've just released up!\n");
	if (input.getMouseDown(0))
	{
		ostringstream ss;
		ss << "We've just pressed the left mouse button at " << input.getMousePosition() << "!\n";
		OutputDebugString(ss.str().c_str());
	}
	if (input.getMouseUp(0))
		OutputDebugString("We've just released the left mouse button!\n");
	if (input.getMouseDown(2))
		OutputDebugString("We've just pressed the right mouse button!\n");
	if (input.getMouseUp(2))
		OutputDebugString("We've just released the right mouse button!\n");
	if (input.getMouseDown(1))
		OutputDebugString("We've just pressed the middle mouse button!\n");
	if (input.getMouseUp(1))
		OutputDebugString("We've just released the middle mouse button!\n");
	if (input.getMouseDown(3))
		OutputDebugString("We've just pressed the 4th mouse button!\n");
	if (input.getMouseUp(3))
		OutputDebugString("We've just released the 4th mouse button!\n");
	if (input.getMouseDown(4))
		OutputDebugString("We've just pressed the 5th mouse button!\n");
	if (input.getMouseUp(4))
		OutputDebugString("We've just released the 5th mouse button!\n");
}

void Game::update()
{
}

void Game::render()
{
}