#pragma once
#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "BaseGameObject.h"
#include "ObjectFactory.h"
#include "vectorMessage.h"
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
		Collider(GameObjects::BaseGameObject *object) : BaseComponent(object) {};
		~Collider() {};
		virtual COLLIDER_TYPE getColliderType() = 0;
		COMPONENT_TYPE getType() { return COMPONENT_TYPE::COLLIDER; };
		void Init() {};
	};

	struct Manifold
	{
		Collider *A;
		Collider *B;
		float penetration;
		glm::vec2 normal;
	};

	class BoxCollider : public Collider
	{
	public:
		BoxCollider(GameObjects::BaseGameObject *object);
		~BoxCollider();

		virtual bool CollideWithBox(Manifold *manifold);
		virtual COLLIDER_TYPE getColliderType();
		void Update();
		void sendMessage(Message *message);

	public:
		glm::vec2 min;
		glm::vec2 max;
		glm::vec2 velocity;
	};

	class CircleCollider : public Collider
	{
	public:
		CircleCollider(float radius, glm::vec2 pos, GameObjects::BaseGameObject *object);
		~CircleCollider();

		virtual bool CollideWithCircle(Manifold *manifold);
		virtual COLLIDER_TYPE getColliderType();

	public:
		float radius;
		glm::vec2 pos;
	};

	class CollisionMessage : Message
	{
	public:
		CollisionMessage(glm::vec2 velocity, glm::vec2 position);
		~CollisionMessage();

	public:
		glm::vec2 velocity;
		glm::vec2 position;
	};
}






















/*class CircleCollider;
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


}*/

#endif // !_COLLIDER_H_