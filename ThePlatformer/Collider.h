#pragma once
#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "BaseGameObject.h"
#include "ObjectFactory.h"
#include <glm/glm.hpp>

namespace GameComponents {
	class CircleCollider;
	class CollisionMessage;

	class BoxCollider : public BaseComponent
	{
	public:
		BoxCollider(GameObjects::BaseGameObject *);
		// min is the top-left corner, max is the bottom-right corner
		BoxCollider(glm::vec2 min, glm::vec2 max);
		~BoxCollider();

		COMPONENT_TYPE getType();
		void Update();
		void Init();

		void sendMessage(Message * message);

		bool Collide(BoxCollider *other);
		bool Collide(CircleCollider *other);

	public:
		glm::vec2 min;
		glm::vec2 max;
	};

	class CircleCollider : BaseComponent
	{
	public:
		CircleCollider();
		CircleCollider(float radius, glm::vec2 pos);
		~CircleCollider();

		COMPONENT_TYPE getType();
		void Update();
		void Init();
		void sendMessage(Message*);

		bool Collide(BoxCollider *other);
		bool Collide(CircleCollider *other);

	private:
		float radius;
		glm::vec2 pos;
	};

	class HexagonCollider : BaseComponent
	{
	public:
		HexagonCollider(GameObjects::BaseGameObject *);
		void sendMessage(Message *);
		~HexagonCollider();

		COMPONENT_TYPE getType();
		void Update();
		void Init();

		bool CollideTop(BoxCollider *other);
		bool CollideDown(BoxCollider *other);
		bool CollideTopLeft(BoxCollider *other);
		bool CollideTopRight(BoxCollider *other);
		bool CollideDownLeft(BoxCollider *other);
		bool CollideDownRight(BoxCollider *other);

	private:
		glm::vec2 top;
		glm::vec2 down;
		glm::vec2 top_left;
		glm::vec2 top_right;
		glm::vec2 down_left;
		glm::vec2 down_right;
	};

	class CollisionMessage : Message
	{
	public:
		CollisionMessage(glm::vec2 pos, glm::vec2 velocity);
		~CollisionMessage();

	public:
		// new position
		glm::vec2 pos;
		// if velocity it's 1, we stop this axe.
		glm::vec2 velocity;
	};
}

#endif // !_COLLIDER_H_