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

	void BodyComponent::Update()
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
		case Message::RIGHT:
			velocity.x = 20.0f;
			break;
		case Message::LEFT:
			velocity.x = -20.0f;
			break;
		case Message::RIGHT_RELEASED:
			velocity.x -= 20.0f;
			break;
		case Message::LEFT_RELEASED:
			velocity.x -= -20.0f;
			break;
		default:
			break;
		}
	}

	void BodyComponent::Integrate(float dt)
	{
		position.x = composition->getX();
		position.y = composition->getY();

		glm::vec2 newForces = (forces * (1.0f / mass));

		acceleration = newForces + gravity;
		velocity += acceleration * dt;

		

		std::cout << position.x << " " << position.y << "       " << velocity.x << " " << velocity.y << "           " << acceleration.x << " " << acceleration.y << std::endl;

		if (position.y > 500 && onGround == false)
		{
			std::cout << "plop" << std::endl;
			acceleration = glm::vec2(0, 0);
			velocity = glm::vec2(0, 0);
			forces = (gravity / (1.0f / mass)) * (-1.0f);
			position.y = 499;
			onGround = true;
			this->composition->SendMessage(new Message(Message::JUMP_RELEASED));
		}
		if (onGround == false) {
			forces = forces + gravity;
		}

		//if (onGround == false)
			position += velocity * dt;

		

		composition->setX(position.x);
		composition->setY(position.y);
		vectorMessage *vec = new vectorMessage(Message::DEBUGVECTOR, velocity);
		this->composition->SendMessage((Message *)vec);


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
		position.x = x;
	}

	void BodyComponent::setPositionY(int y)
	{
		position.y = y;
	}
	int BodyComponent::getPositionX()
	{
		return position.x;
	}
	int BodyComponent::getPositionY()
	{
		return position.y;
	}
}