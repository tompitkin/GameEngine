#pragma once

#include <string>

class ResourceLoader
{
public:
	ResourceLoader();
	~ResourceLoader();
	static std::string loadShader(const std::string& fileName);
};