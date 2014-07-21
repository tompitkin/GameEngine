#pragma once

#include <windows.h>
#include <string>

using namespace std;

class GLWindow
{
public:
	GLWindow();
	~GLWindow();
	void create(int width, int height, char* title);
	void render();
	bool isActive() const;
	bool isKeyDown(int keyCode) const;
	int getWidth() const;
	int getHeight() const;
	string getTitle() const;
	HWND getHWND() const;
	

private:
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
	LRESULT CALLBACK WndProcMem(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
	HINSTANCE hInstance;
	bool active;
	bool keys[256];
	int width;
	int height;
	int pf;
	char* title;
	HWND hWnd;
	HDC hDC;
	HGLRC hGLRC;
};