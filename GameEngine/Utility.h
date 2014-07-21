#pragma once

#define PI 3.1415926535897932385

namespace Utils
{
	template <typename T> 
	T clamp(const T& value, const T& lower, const T&upper)
	{
		return max(lower, min(value, upper));
	}
}