#include "BodyComponent.h"
#include "SpriteComponent.h"

namespace GameComponents {

	BodyComponent::BodyComponent(GameObjects::BaseGameObject *object) : BaseComponent(object)
	{
		object->attachComponent(this);
	}

	BodyComponent::~BodyComponent()
	{
	}

	COMPONENT_TYPE BodyComponent::getType()
	{
		return COMPONENT_TYPE::PHYSIC;
	}

	void BodyComponent::Update(double dt)
	{
		Integrate((float)((dt / 100.0) * 2.0));
	}

	void BodyComponent::Init()
	{
		position = glm::vec2(composition->getX(), composition->getY());
		velocity = glm::vec2(0, 0);
		acceleration = glm::vec2(0, 0);
		mass = this->composition->getMass();
		gravity = glm::vec2(0, 9.8);
		forces = glm::vec2(0, 0);
		onGround = false;
		lastCollisionVelocity = glm::vec2(0, 0);
		isColliding = false;
	}

	void BodyComponent::Init(float intensity, glm::vec2 dir) {
		if (intensity > 0 && this->composition->getType() == GameObjects::PROJECTILE) {
			forces = dir * 150.0f;
			velocity = dir * 50.0f /** intensity / 1500.0f*/;
			gravity = glm::vec2(0, 5.8);
			onGround = false;
		}
	}

	void BodyComponent::sendMessage(GameMessage::Message *message)
	{
		switch (message->id)
		{
		case GameMessage::JUMP:
			if (forces.y == (gravity.y / (1.0f / mass)) * (-1.0f))
			{
				forces.y = -50.0f;
				velocity.y = -50.0f;
				onGround = false;
			}
			break;
		case GameMessage::RIGHT:
			velocity.x = 20.0f;
			isColliding = false;
			break;
		case GameMessage::LEFT:
			velocity.x = -20.0f;
			isColliding = false;
			break;
		case GameMessage::RIGHT_RELEASED:
			if (!isColliding || (lastCollisionVelocity.x > 0 && velocity.x > 0)) velocity.x -= 20.0f;
			if (onGround == true) this->composition->sendMessage(new GameMessage::Message(GameMessage::STAND_ANIMATION));
			break;
		case GameMessage::LEFT_RELEASED:
			if (!isColliding || (lastCollisionVelocity.x < 0 && velocity.x < 0)) velocity.x -= -20.0f;
			if (onGround == true) this->composition->sendMessage(new GameMessage::Message(GameMessage::STAND_ANIMATION));
			break;
		case GameMessage::NO_COLLISION:
			if (onGround == true) this->composition->sendMessage(new GameMessage::Message(GameMessage::JUMP_ANIMATION));
			if (this->composition->getType() != GameObjects::PROJECTILE) forces.y = 0;
			onGround = false;
			break;
		case GameMessage::COLLISION:
			GameMessage::CollisionMessage *collision = (GameMessage::CollisionMessage *)message;
			lastCollisionVelocity = this->velocity;
			this->velocity = collision->velocity;
			this->position += collision->position;
			this->composition->setX((int)position.x);
			this->composition->setY((int)position.y);
			float res = (forces.y * (1.0f / mass)) + gravity.y;
			if (forces.y > 0 && collision->position.y < 0)
			{
				forces = (gravity / (1.0f / mass)) * (-1.0f);
				if (!onGround) this->composition->sendMessage(new GameMessage::Message(GameMessage::STAND_ANIMATION));
				onGround = true;
			}
			else if (res < 0)
			{
				forces.y = 0;
				onGround = false;
			}
			isColliding = true;
			break;
		}
	}

	void BodyComponent::Integrate(float dt)
	{
		position.x = (float) composition->getX();
		position.y = (float) composition->getY();

		glm::vec2 newForces = (forces * (1.0f / mass));

		acceleration = newForces + gravity;
		velocity += acceleration * dt;

		if (onGround == false) forces = forces + gravity;

		position += velocity * dt;

		composition->setX((int) position.x);
		composition->setY((int) position.y);
		GameMessage::VectorMessage *vec = new GameMessage::VectorMessage(GameMessage::VELOCITY_VECTOR, velocity);
		this->composition->sendMessage((GameMessage::Message*)vec);
	}

	void BodyComponent::AddForce(float x, float y)
	{
		forces.x += x;
		forces.y += y;
	}

	void BodyComponent::AddVelocity(float x, float y)
	{
		velocity.x += x;
		velocity.y += y;
	}

	void BodyComponent::setPositionX(int x)
	{
		position.x = (float) x;
	}

	void BodyComponent::setPositionY(int y)
	{
		position.y = (float) y;
	}
	int BodyComponent::getPositionX()
	{
		return (int) position.x;
	}
	int BodyComponent::getPositionY()
	{
		return (int) position.y;
	}
}