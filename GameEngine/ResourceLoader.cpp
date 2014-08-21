#include "ResourceLoader.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include "Mesh.h"
#include "Vertex.h"

ResourceLoader::ResourceLoader()
{
}

ResourceLoader::~ResourceLoader()
{
}

std::string ResourceLoader::loadShader(const std::string& fileName)
{
	std::string shaderSource;
	std::ifstream fileIn;
	std::ostringstream filePath;

	filePath << "./res/shaders/" << fileName;
	fileIn.open(filePath.str());
	
	if (fileIn.is_open())
	{
		std::string line;
		while (std::getline(fileIn, line))
		{
			shaderSource.append(line);
			shaderSource.append("\n");
		}
		fileIn.close();
	}

	return shaderSource;
}

int ResourceLoader::loadMesh(const std::string& fileName, Mesh& mesh)
{
	std::string ext(fileName.substr(fileName.find_last_of('.') + 1));

	if (ext != "obj")
	{
		std::cerr << "ERROR: File format not supported for mesh data: " << ext << '\n';
		return 1;
	}

	std::ifstream fileIn;
	std::ostringstream filePath;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	filePath << "./res/models/" << fileName;
	fileIn.open(filePath.str());

	if (fileIn.is_open())
	{
		std::string line;
		while (std::getline(fileIn, line))
		{
			std::vector<std::string> tokens;
			ResourceLoader::split(std::istringstream(line), tokens, ' ');

			if (tokens[0] == "v")
				vertices.push_back(Vertex(Vector3f(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str()))));
			else if (tokens[0] == "f")
			{
				indices.push_back(atoi(tokens[1].c_str()) - 1);
				indices.push_back(atoi(tokens[2].c_str()) - 1);
				indices.push_back(atoi(tokens[3].c_str()) - 1);
			}
		}
		fileIn.close();
	}

	mesh.addVertices(vertices, indices);

	return 0;
}

void ResourceLoader::split(std::istringstream& input, std::vector<std::string>& tokens, char delimiter)
{
	std::string token;
	while (std::getline(input, token, delimiter))
		tokens.push_back(token);
}