#include "GameEngine.h"

#include "GLWindow.h"
#include "Time.h"
#include "Game.h"
#include "Input.h"
#include "RenderUtil.h"

GameEngine::GameEngine()
{
	isRunning = false;
	window = NULL;
}

GameEngine::~GameEngine()
{
	cleanUp();
}

void GameEngine::start(int width, int height, char* title)
{
	if (isRunning)
		return;

	window = new GLWindow();
	window->create(width, height, title);

	#ifdef _DEBUG
		char msgbuf[30];
		sprintf_s(msgbuf, 30, "GLEW Version: %s\n", (char*)glewGetString(GLEW_VERSION));
		OutputDebugString(msgbuf);
		sprintf_s(msgbuf, 30, "OpenGL Version: %s\n", RenderUtil::getOpenGLVersion().c_str());
		OutputDebugString(msgbuf);
	#endif

	RenderUtil::initGraphics();

	game = new Game();

	run();
}

void GameEngine::stop()
{
	if (!isRunning)
		return;

	isRunning = false;
}

void GameEngine::run()
{
	Time::startTime();

	MSG msg;
	Input input(*window);

	#ifdef _DEBUG
		unsigned _int32 frames = 0;
		long frameCounter = 0;
	#endif

	isRunning = true;

	const double frameTime = 1.0 / FRAME_CAP;

	_int64 lastTime = Time::getTime();
	double unprocessedTime = 0;

	while (isRunning)
	{
		bool frameUpdated = false;

		_int64 startTime = Time::getTime();
		double passedTime = Time::getTimePassedNano(startTime, lastTime);
		lastTime = startTime;

		unprocessedTime += passedTime / (double)Time::SECOND;

		#ifdef _DEBUG
			frameCounter += (long)passedTime;
		#endif

		while (unprocessedTime > frameTime)
		{
			frameUpdated = true;

			unprocessedTime -= frameTime;

			if (PeekMessage(&msg, window->getHWND(), 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					stop();
				else
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}

			Time::setDelta(frameTime);

			game->input(input);
			input.update();

			game->update();

			#ifdef _DEBUG
				if (frameCounter >= Time::SECOND)
				{
					char msgbuf[10];
					sprintf_s(msgbuf, 10, "%d\n", frames);
					OutputDebugString(msgbuf);
					frames = 0;
					frameCounter = 0;
				}
			#endif
		}
		if (frameUpdated)
		{
			render();

			#ifdef _DEBUG
				frames++;
			#endif
		}
		else
			Sleep(1);
	}

	cleanUp();
}

void GameEngine::render()
{
	RenderUtil::clearScreen();
	game->render();
	if (window->isActive())
		window->render();
}

void GameEngine::cleanUp()
{
	delete game;
	game = NULL;

	if (window)
	{
		delete window;
		window = NULL;
	}
}
