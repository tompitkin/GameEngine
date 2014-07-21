#include "GameEngine.h"

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
	MSG msg;
	Time time;
	Input input(*window);

	#ifdef _DEBUG
		unsigned _int32 frames = 0;
		long frameCounter = 0;
	#endif

	isRunning = true;

	const double frameTime = 1.0 / FRAME_CAP;

	_int64 lastTime = time.getTime();
	double unprocessedTime = 0;

	while (isRunning)
	{
		bool frameUpdated = false;

		_int64 startTime = time.getTime();
		double passedTime = time.getTimePassedNano(startTime, lastTime);
		lastTime = startTime;

		unprocessedTime += passedTime / (double)time.SECOND;

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

			time.setDelta(frameTime);
			input.update();

			game.input(input);
			game.update();

			#ifdef _DEBUG
				if (frameCounter >= time.SECOND)
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
	game.render();
	if (window->isActive())
	{
		window->render();
	}
}

void GameEngine::cleanUp()
{
	if (window)
	{
		delete window;
		window = NULL;
	}
}
