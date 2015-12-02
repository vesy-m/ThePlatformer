#pragma once
#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "BaseGameObject.h"
#include "ObjectFactory.h"
#include "CollisionMessage.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

namespace GameComponents {

	enum COLLIDER_TYPE
	{
		BOX = 1,
		CIRCLE,
	};

	struct Manifold
	{
		ColliderComponent *A;
		ColliderComponent *B;
		float penetration;
		glm::vec2 normal;
	};

	class ColliderComponent : public BaseComponent
	{
	public:
		ColliderComponent(GameObjects::BaseGameObject *object) : BaseComponent(object) { object->attachComponent(this); };
		virtual ~ColliderComponent() {};
		virtual void Update(double) = 0;
		virtual COMPONENT_TYPE getType() = 0;
		virtual void Init() = 0;

		void ResolveCollision(Manifold *manifold);
		glm::vec2 ColliderComponent::ClampTest(glm::vec2 point, glm::vec2 minPoint, glm::vec2 maxPoint);
		float Clamp(float min, float max, float value);
		float DotProduct(glm::vec2 a, glm::vec2 b);

		glm::vec2 velocity;
	};	
}

#endif // !_COLLIDER_H_