#pragma once
#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "BaseGameObject.h"
namespace GameComponents {
	class Vector2
	{
	public:
		Vector2();
		Vector2(float x, float y);
		~Vector2();

	private:
		float m_x;
		float m_y;
	};

	class BoxCollider : BaseComponent
	{
	public:
		BoxCollider();
		BoxCollider(Vector2 min, Vector2 max);
		~BoxCollider();

	private:
		Vector2 m_min;
		Vector2 m_max;
	};

	class CircleCollider
	{
	public:
		CircleCollider();
		CircleCollider(float radius, Vector2 pos);
		~CircleCollider();

	private:
		float m_radius;
		Vector2 m_pos;
	};
}

#endif // !_COLLIDER_H_