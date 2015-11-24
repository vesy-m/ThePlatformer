#pragma once
#include "Collider.h"
#include "ObjectFactory.h"

namespace GameComponents {
	class CircleCollider : public ColliderComponent
	{
		friend class GameSystems::ObjectFactory;
	private:
		CircleCollider(GameObjects::BaseGameObject*);
	public:
		virtual ~CircleCollider();

		virtual void Init();
		virtual void Update(double);
		virtual COMPONENT_TYPE getType();
		virtual void sendMessage(GameMessage::Message *message);

		bool CollideWithBox(Manifold *manifold);
	public:
		float radius;
		glm::vec2 centerPos;
		glm::vec2 minPoint;
		glm::vec2 maxPoint;
	};
}

