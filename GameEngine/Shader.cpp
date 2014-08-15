#include "Shader.h"

#include <Windows.h>

Shader::Shader()
{
	program = glCreateProgram();

	if (!program)
		FatalAppExit(NULL, TEXT("Program creation failed."));
}

Shader::~Shader()
{
}

void Shader::addVertexShader(const std::string& data)
{
	addProgram(data, GL_VERTEX_SHADER);
}

void Shader::addGeometryShader(const std::string& data)
{
	addProgram(data, GL_GEOMETRY_SHADER);
}

void Shader::addFragmentShader(const std::string& data)
{
	addProgram(data, GL_FRAGMENT_SHADER);
}

void Shader::compile()
{
	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);

	if (!status)
	{
		GLint infoLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLength);

		GLchar* infoLog = new GLchar[infoLength + 1];
		glGetProgramInfoLog(program, infoLength, NULL, infoLog);
		std::string text(infoLog);
		delete[] infoLog;

		FatalAppExit(NULL, text.c_str());
	}

	glValidateProgram(program);

	glGetProgramiv(program, GL_VALIDATE_STATUS, &status);

	if (!status)
	{
		GLint infoLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLength);

		GLchar* infoLog = new GLchar[infoLength + 1];
		glGetProgramInfoLog(program, infoLength, NULL, infoLog);
		std::string text(infoLog);
		delete[] infoLog;

		FatalAppExit(NULL, text.c_str());
	}
}

void Shader::bind()
{
	glUseProgram(program);
}

void Shader::addProgram(const std::string& data, GLenum type)
{
	GLuint shader = glCreateShader(type);

	if (!shader)
		FatalAppExit(NULL, TEXT("Shader creation failed."));

	const GLchar *shaderData = data.c_str();
	glShaderSource(shader, 1, &shaderData, NULL);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (!status)
	{
		GLint infoLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
		
		GLchar* infoLog = new GLchar[infoLength + 1];
		glGetShaderInfoLog(shader, infoLength, NULL, infoLog);
		std::string text(infoLog);
		delete[] infoLog;
		
		FatalAppExit(NULL, text.c_str());
	}

	glAttachShader(program, shader);
}