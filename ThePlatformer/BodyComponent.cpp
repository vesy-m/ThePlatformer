#include "BodyComponent.h"


namespace GameComponents {

	BodyComponent::BodyComponent(GameObjects::BaseGameObject *object) : BaseComponent(object)
	{
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
		Integrate((dt / 100) * 2);
	}

	void BodyComponent::Init()
	{
		position = glm::vec2(composition->getX(), composition->getY());
		velocity = glm::vec2(0, 0);
		acceleration = glm::vec2(0, 0);
		mass = 100;
		maxForces = 500;
		gravity = glm::vec2(0, 9.8);
		forces = glm::vec2(0, 0);
		onGround = false;
		lastCollisionVelocity = glm::vec2(0, 0);
		isColliding = false;
	}

	void BodyComponent::sendMessage(Message *message)
	{
		switch (message->id)
		{
		case Message::JUMP:
			if (forces == (gravity / (1.0f / mass)) * (-1.0f))
			{
				forces.y = -50.0f;
				velocity.y = -50.0f;
				onGround = false;
			}
			break;
		case Message::FIRE:
		{
			if (this->composition->getType() == GameObjects::PROJECTILE) {
				forces.y = -250.0f;
				forces.x = 150.0f;
				velocity.y = -35.0f;
				velocity.x = 25.0f;
				maxForces = 100;
				onGround = false;
			}
			break;
		}
		case Message::RIGHT:
			forces.x = 20.0f;
			velocity.x = 20.0f;
			isColliding = false;
			break;
		case Message::LEFT:
			forces.x = -20.0f;
			velocity.x = -20.0f;
			isColliding = false;
			break;
		case Message::RIGHT_RELEASED:
			if (!isColliding || (lastCollisionVelocity.x > 0 && velocity.x > 0))
			{
				forces.x -= 20.0f;
				velocity.x -= 20.0f;
			}
			if (onGround == true)
				this->composition->sendMessage(new Message(Message::STAND_ANIMATION));
			break;
		case Message::LEFT_RELEASED:
			if (!isColliding || (lastCollisionVelocity.x < 0 && velocity.x < 0))
			{
				forces.x -= -20.0f;
				velocity.x -= -20.0f;
			}
			if (onGround == true)
				this->composition->sendMessage(new Message(Message::STAND_ANIMATION));
			break;
		case Message::NO_COLLISION:
			if (onGround == true)
				this->composition->sendMessage(new Message(Message::JUMP_ANIMATION));
			//forces.y = 0;
			onGround = false;
			break;
		case Message::COLLISION:
			GameComponents::CollisionMessage *collision = (GameComponents::CollisionMessage *)message;
			lastCollisionVelocity = this->velocity;
			this->velocity = collision->velocity;
			this->position += collision->position;
			this->composition->setX((int)position.x);
			this->composition->setY((int)position.y);
			float res = (forces.y * (1.0f / mass)) + gravity.y;
			if (forces.y > 0 && collision->position.y < 0)
			{
				forces = (gravity / (1.0f / mass)) * (-1.0f);
				if (!onGround)
					this->composition->sendMessage(new Message(Message::STAND_ANIMATION));
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
		//if (this->composition->getType() == GameObjects::PROJECTILE)
		//{
			position.x = (float) composition->getX();
			position.y = (float) composition->getY();

			glm::vec2 newForces = (forces * (1.0f / mass));

			acceleration = newForces + gravity;
			velocity += acceleration * dt;

			//std::cout << forces.x << "\t\t" << forces.y << std::endl;

			if (onGround == false) {
				forces = forces + gravity;
			}

			position += velocity * dt;

			composition->setX((int) position.x);
			composition->setY((int) position.y);
			VectorMessage *vec = new VectorMessage(Message::VELOCITY_VECTOR, velocity);
			this->composition->sendMessage((Message *)vec);
		//}
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