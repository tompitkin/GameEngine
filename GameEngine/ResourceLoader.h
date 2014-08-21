#pragma once

#include <string>
#include <vector>

class Mesh;

class ResourceLoader
{
public:
	ResourceLoader();
	~ResourceLoader();
	static std::string loadShader(const std::string& fileName);
	static int loadMesh(const std::string& fileName, Mesh& mesh);

private:	
	static void split(std::istringstream& input, std::vector<std::string>& tokens, char delimiter);
};