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

	void BodyComponent::Update(double)
	{
		Integrate(0.3f);
	}

	void BodyComponent::Init()
	{
		position = glm::vec2(composition->getX(), composition->getY());
		velocity = glm::vec2(0, 0);
		acceleration = glm::vec2(0, 0);
		mass = 20;
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
				forces.y = -350.0f;
				forces.x = 150.0f;
				velocity.y = -35.0f;
				velocity.x = 25.0f;
				onGround = false;
			}
			break;
		}
		case Message::RIGHT:
			//if (onGround == true)
			//this->composition->SendMessage(new Message(Message::RIGHT_ANIMATION));
			velocity.x = 20.0f;
			isColliding = false;
			break;
		case Message::LEFT:
			//if (onGround == true)
			//this->composition->SendMessage(new Message(Message::LEFT_ANIMATION));
			velocity.x = -20.0f;
			isColliding = false;
			break;
		case Message::RIGHT_RELEASED:
			if (!isColliding || (lastCollisionVelocity.x > 0 && velocity.x > 0))
				velocity.x -= 20.0f;
			if (onGround == true)
				this->composition->sendMessage(new Message(Message::STAND_ANIMATION));
			break;
		case Message::LEFT_RELEASED:
			if (!isColliding || (lastCollisionVelocity.x < 0 && velocity.x < 0))
				velocity.x -= -20.0f;
			if (onGround == true)
				this->composition->sendMessage(new Message(Message::STAND_ANIMATION));
			break;
		case Message::NO_COLLISION:
			if (onGround == true)
				this->composition->sendMessage(new Message(Message::JUMP_ANIMATION));
			forces.y = 0;
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
			/*case Message::COLLISION:
			GameComponents::CollisionMessage *collision = (GameComponents::CollisionMessage *)message;
			lastCollisionVelocity = velocity;
			float res = (forces.y * (1.0f / mass)) + gravity.y;
			if (collision->velocity.x == 1)
			velocity.x = 0;
			if (collision->velocity.y == 1)
			{

			if (forces.y > 0)
			{
			forces = (gravity / (1.0f / mass)) * (-1.0f);
			if (!onGround)
			this->composition->sendMessage(new Message(Message::STAND_ANIMATION));
			onGround = true;
			}
			else if (res < 0)
			{
			forces.y = 0;
			}
			velocity.y = 0;
			}
			position = collision->pos;
			composition->setX((int)position.x);
			composition->setY((int)position.y);
			isColliding = true;
			break;*/
		}
	}

	void BodyComponent::Integrate(float dt)
	{
		position.x = (float) composition->getX();
		position.y = (float) composition->getY();

		glm::vec2 newForces = (forces * (1.0f / mass));

		acceleration = newForces + gravity;
		velocity += acceleration * dt;

		

		//std::cout << position.x << " " << position.y << "       " << velocity.x << " " << velocity.y << "           " << acceleration.x << " " << acceleration.y << std::endl;

		if (onGround == false) {
			forces = forces + gravity;
		}

		position += velocity * dt;

		composition->setX((int) position.x);
		composition->setY((int) position.y);
		VectorMessage *vec = new VectorMessage(Message::VELOCITY_VECTOR, velocity);
		this->composition->sendMessage((Message *)vec);


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





		//position = glm::vec2(position.x /*+ (velocity.x * dt)*/, position.y + (dt * ((velocity + temp) / 2)));

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