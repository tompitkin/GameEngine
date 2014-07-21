#include "Input.h"

const int Input::remapMouse[] = { VK_LBUTTON, VK_MBUTTON, VK_RBUTTON, VK_XBUTTON1, VK_XBUTTON2 };

Input::Input(const GLWindow &window) : win(window)
{
}

Input::~Input()
{
}

void Input::update()
{
	upKeys.clear();

	for (int i = 0; i < NUM_KEYCODES; i++)
	{
		if (!getKey(i) && find(currentKeys.begin(), currentKeys.end(), i) != currentKeys.end())
			upKeys.push_back(i);
	}

	downKeys.clear();
	
	for (int i = 0; i < NUM_KEYCODES; i++)
	{
		if (getKey(i) && find(currentKeys.begin(), currentKeys.end(), i) == currentKeys.end())
			downKeys.push_back(i);
	}

	currentKeys.clear();

	for (int i = 0; i < NUM_KEYCODES; i++)
	{
		if (getKey(i))
			currentKeys.push_back(i);
	}
}

bool Input::getKey(unsigned int keyCode) const
{
	if (keyCode < NUM_KEYCODES)
		return win.isKeyDown(keyCode);
	return false;
}

bool Input::getKeyDown(unsigned int keyCode) const
{
	if (keyCode < NUM_KEYCODES)
		return (find(downKeys.begin(), downKeys.end(), keyCode) != downKeys.end());
	return false;
}

bool Input::getKeyUp(unsigned int keyCode) const
{
	if (keyCode < NUM_KEYCODES)
		return (find(upKeys.begin(), upKeys.end(), keyCode) != upKeys.end());
	return false;
}

bool Input::getMouse(unsigned int mouseButton) const
{
	if (mouseButton < NUM_MOUSEBUTTONS)
		return getKey(remapMouse[mouseButton]);
	return false;
}

bool Input::getMouseDown(unsigned int mouseButton) const
{
	if (mouseButton < NUM_MOUSEBUTTONS)
		return getKeyDown(remapMouse[mouseButton]);
	return false;
}

bool Input::getMouseUp(unsigned int mouseButton) const
{
	if (mouseButton < NUM_MOUSEBUTTONS)
		return getKeyUp(remapMouse[mouseButton]);
	return false;
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