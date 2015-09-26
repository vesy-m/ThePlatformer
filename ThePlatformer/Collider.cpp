#include "Collider.h"

namespace GameComponents {
	BoxCollider::BoxCollider()
	{}

	BoxCollider::BoxCollider(glm::vec2 min, glm::vec2 max)
	{
		this->min = min;
		this->max = max;
	}

	BoxCollider::~BoxCollider()
	{}

	bool BoxCollider::Collide(BoxCollider *other)
	{
		// Exit with no intersection if found separated along an axis
		if (this->max.x < other->min.x || this->min.x > other->max.x)
			return false;
		if (this->max.y < other->min.y || this->min.y > other->max.y)
			return false;

		// No separating axis found, therefor there is at least one overlapping axis
		return true;
	}

	bool BoxCollider::Collide(CircleCollider * other)
	{
		return false;
	}

	CircleCollider::CircleCollider()
	{}

	CircleCollider::CircleCollider(float radius, glm::vec2 pos)
	{
		this->radius = radius;
		this->pos = pos;
	}

	CircleCollider::~CircleCollider()
	{}

	bool CircleCollider::Collide(BoxCollider * other)
	{
		return false;
	}

	bool CircleCollider::Collide(CircleCollider *other)
	{
		float r = this->radius + other->radius;
		r *= r;
		return r < pow((this->pos.x + other->pos.x), 2) + pow((this->pos.y + other->pos.y), 2);
	}
}