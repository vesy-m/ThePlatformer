#include "Collider.h"

namespace GameComponents {

	float Clamp(float min, float max, float value)
	{
		return std::min(std::max(value, min), max);
	}

	float DotProduct(glm::vec2 a, glm::vec2 b)
	{
		return (a.x * b.x) + (a.y * b.y);
	}

}