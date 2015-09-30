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
		Integrate(0.3);
	}

	void BodyComponent::Init()
	{
		position = glm::vec2(composition->getX(), composition->getY());
		velocity = glm::vec2(0.0, 0.0);
		acceleration = 0;
		mass = 1;
		gravity = 9.80;
		forces = 0;
	}

	void BodyComponent::Integrate(float dt)
	{
		position.x = composition->getX();
		position.y = composition->getY();

		double temp = acceleration * dt;

		position = glm::vec2(position.x /*+ (velocity.x * dt)*/, position.y + (dt * ((velocity.y + temp) / 2)));

		/*pos = pos + dt*(vel + temp / 2);
		vel = vel + temp;*/


		//position = glm::vec2(position.x /*+ (velocity.x * dt)*/, position.y + (velocity.y * dt));

		composition->setX(position.x);
		composition->setY(position.y);

		if (position.y < 550)
		{
		
			acceleration = (forces * mass) + gravity;
			velocity = glm::vec2(velocity.x + temp, velocity.y + temp);
		}
		else
		{
			acceleration = (forces * mass);
			velocity.x = 0;
			velocity.y = 0;
		}


		//if (velocity.x < 300 && velocity.y < 300)
			//velocity = glm::vec2(velocity.x + (acceleration * dt), velocity.y + (acceleration * dt));

	}

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