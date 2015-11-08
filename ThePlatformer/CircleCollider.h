#pragma once
#ifndef _CIRCLECOLLIDER_H_
#define _CIRCLECOLLIDER_H_

#include "Collider.h"

namespace GameComponents {
	class CircleCollider : public Collider
	{
		friend class GameSystems::ObjectFactory;
	public:
		virtual ~CircleCollider();
		virtual bool CollideWithCircle(Manifold *manifold);
		virtual bool CollideWithBox(Manifold *manifold);
		virtual COLLIDER_TYPE getColliderType();
		virtual void Update(double);
		void sendMessage(GameMessage::Message *message);
		virtual void Init() {}

	public:
		float radius;
		glm::vec2 pos;
	private:
		CircleCollider(GameObjects::BaseGameObject *object);
	};
}

#endif // !_CIRCLECOLLIDER_H_
