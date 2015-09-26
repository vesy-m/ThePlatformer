#pragma once
#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "BaseGameObject.h"
#include <glm/glm.hpp>

namespace GameComponents {
	class CircleCollider;

	class BoxCollider : BaseComponent
	{
	public:
		BoxCollider();
		// min is the top-left corner, max is the bottom-right corner
		BoxCollider(glm::vec2 min, glm::vec2 max);
		~BoxCollider();
		bool Collide(BoxCollider *other);
		bool Collide(CircleCollider *other);

	private:
		glm::vec2 min;
		glm::vec2 max;
	};

	class CircleCollider : BaseComponent
	{
	public:
		CircleCollider();
		CircleCollider(float radius, glm::vec2 pos);
		~CircleCollider();
		bool Collide(BoxCollider *other);
		bool Collide(CircleCollider *other);

	private:
		float radius;
		glm::vec2 pos;
	};
}

#endif // !_COLLIDER_H_