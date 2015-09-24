#include "Collider.h"

namespace GameComponents {
	Vector2::Vector2(float x, float y)
	{
		m_x = x;
		m_y = y;
	}


	Vector2::~Vector2()
	{
	}

	BoxCollider::BoxCollider()
	{
	}

	BoxCollider::BoxCollider(Vector2 min, Vector2 max)
	{
		m_min = min;
		m_max = max;
	}


	BoxCollider::~BoxCollider()
	{
	}

	CircleCollider::CircleCollider()
	{
	}

	CircleCollider::CircleCollider(float radius, Vector2 pos)
	{
		m_radius = radius;
		m_pos = pos;
	}

	CircleCollider::~CircleCollider()
	{
	}
}