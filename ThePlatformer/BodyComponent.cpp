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
		Integrate((float)((dt / 100.0f) * 2.0f));
	}

	void BodyComponent::Init()
	{
		position = glm::vec2(composition->getX(), composition->getY());
		velocity = glm::vec2(0.0f, 0.0f);
		mass = this->composition->getMass();
		gravity = glm::vec2(0.0f, 9.80f);
		forces = glm::vec2(0.0f, 0.0f);
		maxForce = 500.0f;
		onGround = false;
		lastCollisionVelocity = glm::vec2(0.0f, 0.0f);
		isColliding = false;
	}

	void BodyComponent::Init(float intensity, glm::vec2 dir) {
		if (intensity > 0 && this->composition->getType() == GameObjects::PROJECTILE) {
			forces = dir * 150.0f;
			maxForce = 200.0f;
			velocity = dir * 50.0f /** intensity / 1500.0f*/;
			gravity = glm::vec2(0.0f, 5.80f);
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
			if (forces.y > 0 && collision->normal.y < 0.0f)
			{
				/*if (composition->getType() == GameObjects::PROJECTILE)
					gravity.y = 0.0f;*/
				forces = (gravity / (1.0f / mass)) * (-1.0f);
				if (!onGround) this->composition->sendMessage(new GameMessage::Message(GameMessage::STAND_ANIMATION));
				onGround = true;
			}
			else if (res < 0.0f)
			{
				forces.y = 0.0f;
				onGround = false;
			}

			if (velocity.x == 0.0f)
				forces.x = 0.0f;
			isColliding = true;
			break;
		}
	}

	void BodyComponent::Integrate(float dt)
	{
		//std::cout << dt << std::endl;
		position.x = (float) composition->getX();
		position.y = (float) composition->getY();

		glm::vec2 newForces = (forces * (1.0f / mass));

		/*if (composition->getType() == GameObjects::PROJECTILE)
			std::cout << newForces.x << " / " << newForces.y << std::endl;*/

		glm::vec2 acceleration = newForces + gravity;
		if (acceleration.y >= -0.0001f && acceleration.y <= 0.0001f)
			acceleration.y = 0.0f;
		velocity += acceleration * dt;
		/*if (composition->getType() == GameObjects::PROJECTILE)
		{
			this->m_log_file << "Velocity:\t" << velocity.x << "\t" << velocity.y << std::endl;
			this->m_log_file << "Acceleration:\t" << acceleration.x << "\t" << acceleration.y << std::endl;
		}*/

		if (onGround == false && (forces.y <= maxForce)) forces = forces + gravity;

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