#pragma once

#include <gl\glew.h>
#include <vector>

class Vertex;

class Mesh
{
public:
	Mesh();
	~Mesh();
	void addVertices(const std::vector<Vertex>& vertices);
	void draw() const;

private:
	GLuint vbo;
	GLsizeiptr size;
};

