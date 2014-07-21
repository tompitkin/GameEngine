#include "Input.h"

const int Input::remapMouse[] = { VK_LBUTTON, VK_MBUTTON, VK_RBUTTON, VK_XBUTTON1, VK_XBUTTON2 };

Input::Input(const GLWindow &window) : 
win(window), lastKeys(NUM_KEYCODES, false), lastMouse(NUM_MOUSEBUTTONS, false)
{
}

Input::~Input()
{
}

void Input::update()
{
	for (int i = 0; i < NUM_KEYCODES; i++)
		lastKeys[i] = getKey(i);

	for (int i = 0; i < NUM_MOUSEBUTTONS; i++)
		lastMouse[i] = getMouse(i);
}

bool Input::getKey(unsigned int keyCode) const
{
	return win.isKeyDown(keyCode);
}

bool Input::getKeyDown(unsigned int keyCode) const
{
	return getKey(keyCode) && !lastKeys[keyCode];
}

bool Input::getKeyUp(unsigned int keyCode) const
{
	return !getKey(keyCode) && lastKeys[keyCode];
}

bool Input::getMouse(unsigned int mouseButton) const
{
	return getKey(remapMouse[mouseButton]);
}

bool Input::getMouseDown(unsigned int mouseButton) const
{
	return getKeyDown(remapMouse[mouseButton]);
}

bool Input::getMouseUp(unsigned int mouseButton) const
{
	return getKeyUp(remapMouse[mouseButton]);
}

Vector2f Input::getMousePosition() const
{
	POINT p;
	if (GetCursorPos(&p) && ScreenToClient(win.getHWND(), &p))
	{
		float x = (float)min((unsigned int)p.x, (unsigned int)win.getWidth() - 1);
		float y = (float)min((unsigned int)p.y, (unsigned int)win.getHeight() - 1);
		return Vector2f(x, y);
	}
	return Vector2f(0, 0);
}