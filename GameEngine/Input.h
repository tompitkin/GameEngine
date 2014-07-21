#pragma once

#include <vector>
#include "GLWindow.h"
#include "Vector2f.h"

class Input
{
public:
	Input(const GLWindow &window);
	~Input();
	void update();
	bool getKey(unsigned int keyCode) const;
	bool getKeyDown(unsigned int keyCode) const;
	bool getKeyUp(unsigned int keyCode) const;
	bool getMouse(unsigned int mouseButton) const;
	bool getMouseDown(unsigned int mouseButton) const;
	bool getMouseUp(unsigned int mouseButton) const;
	Vector2f getMousePosition() const;
	static const int NUM_KEYCODES = 256;
	static const int NUM_MOUSEBUTTONS = 5;

private:
	static const int remapMouse[];
	const GLWindow &win;
	vector<bool> lastKeys;
	vector<bool> lastMouse;
};