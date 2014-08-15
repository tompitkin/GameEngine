#pragma once

#include <vector>

class Vertex;

#define PI 3.1415926535897932385

namespace Utils
{
	template <typename T> T clamp(const T& value, const T& lower, const T&upper);
	void createBuffer(const std::vector<Vertex>& vertices, std::vector<float>& buffer);
}