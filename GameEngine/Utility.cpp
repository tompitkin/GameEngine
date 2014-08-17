#include "Utility.h"

#include "Vertex.h"

template <typename T> T Utils::clamp(const T& value, const T& lower, const T&upper)
{
		return max(lower, min(value, upper));
}

void Utils::createFloatBuffer(const std::vector<Vertex>& vertices, std::vector<float>& buffer)
{
	buffer.clear();
	buffer.reserve(vertices.size() * Vertex::SIZE);

	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		buffer.push_back(vertices[i].getPos().getX());
		buffer.push_back(vertices[i].getPos().getY());
		buffer.push_back(vertices[i].getPos().getZ());
	}
}