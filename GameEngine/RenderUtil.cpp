#include "RenderUtil.h"

void RenderUtil::clearScreen()
{
	//TODO Stencil Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderUtil::initGraphics()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	//TODO Depth Clamp

	glEnable(GL_FRAMEBUFFER_SRGB);
}