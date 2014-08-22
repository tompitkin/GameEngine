#include "Game.h"

#include <Windows.h>
#include <vector>
#include <sstream>
#include <string>
#include "Vector3f.h"
#include "Vector2f.h"
#include "Vertex.h"
#include "Input.h"
#include "ResourceLoader.h"
#include "Time.h"
#include "Matrix4f.h"


Game::Game()
{
	/*const Vertex dataV[] = { Vertex(Vector3f(-1, -1, 0)), Vertex(Vector3f(0, 1, 0)), Vertex(Vector3f(1, -1, 0)), Vertex(Vector3f(0, -1, 1)) };
	std::vector<Vertex> verts(dataV, dataV + sizeof(dataV) / sizeof(dataV[0]));

	const unsigned int dataI[] = { 0, 1, 3, 3, 1, 2, 2, 1, 0, 0, 2, 3};
	std::vector<unsigned int> indices(dataI, dataI + sizeof(dataI) / sizeof(dataI[0]));

	mesh.addVertices(verts, indices);*/

	ResourceLoader::loadMesh("bigmonkey.obj", mesh);

	shader.addVertexShader(ResourceLoader::loadShader("basicVert.vs"));
	shader.addFragmentShader(ResourceLoader::loadShader("basicFrag.fs"));
	shader.compile();

	shader.addUniform("transform");
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
		std::ostringstream ss;
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
	timePassed += Time::getDelta();

	float sinWave = std::sin(timePassed);

	trans.setTranslation(sinWave, 0, 0);
	trans.setRotation(0, sinWave * 180, 0);
	trans.setScale(0.5, 0.5, 0.5);
}

void Game::render()
{
	shader.bind();
	shader.setUniform("transform", trans.getTransformation());
	mesh.draw();
}