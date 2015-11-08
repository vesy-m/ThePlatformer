#pragma once
#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "BaseGameObject.h"
#include "ObjectFactory.h"
#include "CollisionMessage.h"
#include <glm/glm.hpp>

namespace GameComponents {

	enum COLLIDER_TYPE
	{
		BOX = 1,
		CIRCLE,
	};

	class Collider : public BaseComponent
	{
	public:
		Collider(GameObjects::BaseGameObject *object) : BaseComponent(object) { object->attachComponent(this); };
		virtual ~Collider() {};
		virtual COLLIDER_TYPE getColliderType() = 0;
		virtual void Update(double) = 0;
		virtual COMPONENT_TYPE getType() { return COMPONENT_TYPE::COLLIDER; };
		virtual void Init() = 0;

		glm::vec2 velocity;
	};

	struct Manifold
	{
		Collider *A;
		Collider *B;
		float penetration;
		glm::vec2 normal;
	};

	float Clamp(float min, float max, float value);
	float DotProduct(glm::vec2 a, glm::vec2 b);

}

#endif // !_COLLIDER_H_