#include "Mesh.h"

#include "Vertex.h"
#include "Utility.h"

Mesh::Mesh()
{
	glGenBuffers(1, &vbo);
	size = 0;
}

Mesh::~Mesh()
{
}

void Mesh::addVertices(const std::vector<Vertex>& vertices)
{
	std::vector<GLfloat> verts;
	Utils::createBuffer(vertices, verts);

	size = vertices.size();

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(verts[0]), &verts[0], GL_STATIC_DRAW);
}

void Mesh::draw() const
{
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, Vertex::SIZE * 4, 0);

	glDrawArrays(GL_TRIANGLES, 0, size);

	glDisableVertexAttribArray(0);
}