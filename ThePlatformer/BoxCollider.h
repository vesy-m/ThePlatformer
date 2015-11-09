#pragma once
#ifndef _BOXCOLLIDER_H_
#define _BOXCOLLIDER_H_

#include "Collider.h"
#include "ObjectFactory.h"

namespace GameComponents {
	class BoxCollider : public Collider
	{
		friend class GameSystems::ObjectFactory;
	private:
		BoxCollider(GameObjects::BaseGameObject*);
	public:
		virtual ~BoxCollider();
		virtual bool CollideWithBox(Manifold *manifold);
		virtual COLLIDER_TYPE getColliderType();
		virtual void Update(double);
		virtual void sendMessage(GameMessage::Message *message);
		virtual void Init();
	public:
		glm::vec2 min;
		glm::vec2 max;

	};

	void ResolveCollision(Manifold *manifold);
}

#endif // !_BOXCOLLIDER_H_

