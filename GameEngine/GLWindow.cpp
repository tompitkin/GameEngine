#include "GLWindow.h"

GLWindow::GLWindow() : keys(256, false)
{
	active = false;
	width = 0;
	height = 0;
	pf = 0;
	title = "";
	hWnd = NULL;
	hDC = NULL;
	hGLRC = NULL;
}

GLWindow::~GLWindow()
{
	if (hGLRC)
	{
		if (!wglMakeCurrent(NULL, NULL))
			FatalAppExit(NULL, TEXT("Failed to release the rendering context."));
		if (!wglDeleteContext(hGLRC))
			FatalAppExit(NULL, TEXT("Failed to delete the rendering context."));
		hGLRC = NULL;
	}
	if (hDC && !ReleaseDC(hWnd, hDC))
	{
		FatalAppExit(NULL, TEXT("Failed to release the device context."));
		hDC = NULL;
	}
	if (hWnd && !DestroyWindow(hWnd))
	{
		FatalAppExit(NULL, TEXT("Failed to destroy the window."));
		hWnd = NULL;
	}
	if (!UnregisterClass("OpenGL", hInstance))
	{
		FatalAppExit(NULL, TEXT("Failed to unregister Class."));
		hInstance = NULL;
	}
}

void GLWindow::create(int width, int height, char* title)
{
	this->width = width;
	this->height = height;
	this->title = title;

	hInstance = GetModuleHandle(NULL);

	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "OpenGL";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	if (!RegisterClass(&wc))
		FatalAppExit(NULL, TEXT("Failed to register the Window class."));

	RECT rect;
	SetRect(&rect, 0, 0, width, height);
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	hWnd = CreateWindow("OpenGL", title, WS_OVERLAPPEDWINDOW, 0, 0, width, height, NULL, NULL, hInstance, NULL);
	if (!hWnd)
		FatalAppExit(NULL, TEXT("Window creation error."));

	SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)this);

	if (!(hDC = GetDC(hWnd)))
		FatalAppExit(NULL, TEXT("Can't get a device context."));

	static PIXELFORMATDESCRIPTOR pfd = { 0 };
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 32;

	if (!(pf = ChoosePixelFormat(hDC, &pfd)))
		FatalAppExit(NULL, TEXT("Can't find a suitable PixelFormat."));

	if (!SetPixelFormat(hDC, pf, &pfd))
		FatalAppExit(NULL, TEXT("Can't set the PixelFormat."));

	if (!(hGLRC = wglCreateContext(hDC)))
		FatalAppExit(NULL, TEXT("Can't create a GL rendering context."));

	if (!wglMakeCurrent(hDC, hGLRC))
		FatalAppExit(NULL, TEXT("Can't activate the GL rendering context."));

	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
}

LRESULT CALLBACK GLWindow::WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	GLWindow* pThis = (GLWindow*)(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	if (pThis)
		return pThis->WndProcMem(hwnd, message, wparam, lparam);
	return DefWindowProc(hwnd, message, wparam, lparam);
}

LRESULT CALLBACK GLWindow::WndProcMem(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_ACTIVATE:
		if (!HIWORD(wparam))
			active = true;
		else
			active = false;
		return 0;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		keys[wparam] = true;
		return 0;
	case WM_KEYUP:
		keys[wparam] = false;
		return 0;
	case WM_LBUTTONDOWN:
		keys[VK_LBUTTON] = true;
		return 0;
	case WM_LBUTTONUP:
		keys[VK_LBUTTON] = false;
		return 0;
	case WM_MBUTTONDOWN:
		keys[VK_MBUTTON] = true;
		return 0;
	case WM_MBUTTONUP:
		keys[VK_MBUTTON] = false;
		return 0;
	case WM_RBUTTONDOWN:
		keys[VK_RBUTTON] = true;
		return 0;
	case WM_RBUTTONUP:
		keys[VK_RBUTTON] = false;
		return 0;
	case WM_XBUTTONDOWN:
		keys[4 + GET_XBUTTON_WPARAM(wparam)] = true;
		return 0;
	case WM_XBUTTONUP:
		keys[4 + GET_XBUTTON_WPARAM(wparam)] = false;
		return 0;
	}

	return DefWindowProc(hwnd, message, wparam, lparam);
}

void GLWindow::render()
{
	SwapBuffers(hDC);
}

bool GLWindow::isActive() const
{
	return active;
}

bool GLWindow::isKeyDown(int keyCode) const
{
	return keys[keyCode];
}

int GLWindow::getWidth() const
{
	return width;
}

int GLWindow::getHeight() const
{
	return height;
}

string GLWindow::getTitle()const
{
	return title;
}

HWND GLWindow::getHWND() const
{
	return hWnd;
}
