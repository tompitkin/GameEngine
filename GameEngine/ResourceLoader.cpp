#include "ResourceLoader.h"

#include <sstream>
#include <fstream>

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
	
	std::string line;
	if (fileIn.is_open())
	{
		while (std::getline(fileIn, line))
		{
			shaderSource.append(line);
			shaderSource.append("\n");
		}
		fileIn.close();
	}

	return shaderSource;
}