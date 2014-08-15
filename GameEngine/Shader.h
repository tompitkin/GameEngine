#pragma once

#include <gl/glew.h>
#include <string>

class Shader
{
public:
	Shader();
	~Shader();

	void addVertexShader(const std::string& data);
	void addGeometryShader(const std::string& data);
	void addFragmentShader(const std::string& data);
	void compile();
	void bind();

private:
	void addProgram(const std::string& data, GLenum type);
	GLuint program;
};

