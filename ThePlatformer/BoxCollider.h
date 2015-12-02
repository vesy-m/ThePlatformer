#pragma once
#ifndef _BOXCOLLIDER_H_
#define _BOXCOLLIDER_H_

#include "Collider.h"
#include "ObjectFactory.h"

namespace GameComponents {
	class BoxCollider : public ColliderComponent
	{
		friend class GameSystems::ObjectFactory;
	private:
		BoxCollider(GameObjects::BaseGameObject*);
	public:
		virtual ~BoxCollider();
		virtual COMPONENT_TYPE getType();
		virtual void Update(double);
		virtual void sendMessage(GameMessage::Message*);
		virtual void Init();

		bool CollideWithBox(Manifold *manifold);
	public:
		glm::vec2 centerPos;
		glm::vec2 minPoint;
		glm::vec2 maxPoint;

	};
}

#endif // !_BOXCOLLIDER_H_

