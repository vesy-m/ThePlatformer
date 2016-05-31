#include "BodyComponent.h"
#include "SpriteComponent.h"

namespace GameComponents {

	BodyComponent::BodyComponent(GameObjects::BaseGameObject *object) : BaseComponent(object)
	{
		object->attachComponent(this);
		this->parentObject = nullptr;
	}

	BodyComponent::~BodyComponent()
	{
	}

	COMPONENT_TYPE BodyComponent::getType() const
	{
		return COMPONENT_TYPE::PHYSIC;
	}

	void BodyComponent::Update(double dt)
	{
		if (this->composition->getType() == GameObjects::PROJECTILE && this->composition->getProjectileType() == GameObjects::PUNCH) {
			if (!this->parentObject)
				return;
			int parentPosX = parentObject->getX();
			int parentPosY = parentObject->getY();

			int centerX = (parentPosX + (this->parentObject->getWidth() / 2));
			int centerY = (parentPosY + (this->parentObject->getHeight() / 2));
			GameComponents::SpriteComponent *sprite = reinterpret_cast<GameComponents::SpriteComponent*>(this->parentObject->getComponent(GameComponents::SPRITE));

			glm::vec2 direction = glm::vec2(100.0, 100.0);
			if (sprite->revertX) direction = glm::vec2((-100 + centerX) - centerX, (centerY)-centerY);
			else direction = glm::vec2((100 + centerX) - centerX, (centerY)-centerY);

			if (direction.x <= 0)
				this->getComposition()->setX(parentPosX - (this->parentObject->getWidth() / 2));
			else if (direction.x > 0)
				this->getComposition()->setX(parentPosX + (this->parentObject->getWidth() / 2) + 5);
			this->getComposition()->setY(parentPosY + (this->parentObject->getHeight() / 2) - 15);
		}
		else
			Integrate((float)(dt / 100));
	}

	void BodyComponent::Init()
	{
		position = glm::vec2(composition->getX(), composition->getY());
		velocity = glm::vec2(0.0f, 0.0f);
		mass = this->composition->getMass();
		movementSpeed = this->composition->getMoveSpeed();
		gravity = glm::vec2(0.0f, 9.80f);
		forces = glm::vec2(0.0f, 0.0f);
		maxForce = 500.0f;
		onGround = false;
		lastCollisionVelocity = glm::vec2(0.0f, 0.0f);
		isColliding = false;
		isDash = false;
		stopLeft = false;
		stopRight = false;
	}

	void BodyComponent::Init(float intensity, glm::vec2 dir) {
		if (intensity > 0 && (this->composition->getType() == GameObjects::PROJECTILE ||
							  this->composition->getType() == GameObjects::PROJECTILE_BREAK)) {
			if (this->composition->getName().find("baseballPlayer") != std::string::npos) {
				forces = dir * 150.0f;
				maxForce = 200.0f;
				velocity = dir * 50.0f;
			} 
			else if (this->composition->getName().find("footballPlayer") != std::string::npos) {
				forces = dir * 150.0f;
				maxForce = 200.0f;
				velocity = dir * 50.0f;
			}
			else if (this->composition->getName().find("tennisPlayer") != std::string::npos) {
				forces = dir * 400.0f;
				maxForce = 200.0f;
				velocity = dir * 50.0f;
			}
			else if (this->composition->getName().find("boxerPlayer") != std::string::npos) {
				forces = dir * 400.0f;
				maxForce = 200.0f;
				velocity = dir * 50.0f;
			}
			gravity = glm::vec2(0.0f, 5.8f);
			onGround = false;
		}
	}

	void BodyComponent::sendMessage(GameMessage::Message *message)
	{
		switch (message->id)
		{
		case GameMessage::BLOCK:
			isDash = true;
			velocity.x = 0;
			isColliding = false;
			break;
		case GameMessage::STOP_BLOCK:
			isDash = false;
			break;
		case GameMessage::STOP_DASH:
			isDash = false;
			if (!isColliding || (lastCollisionVelocity.x > 0 && velocity.x > 0))
				velocity.x -= 40.0f;
			else if (!isColliding || (lastCollisionVelocity.x < 0 && velocity.x < 0))
				velocity.x += 40.0f;
			if (onGround == true)
				this->composition->sendMessage(new GameMessage::Message(GameMessage::STAND_ANIMATION));
			break;
		case GameMessage::JUMP:
			if (forces.y == (gravity.y / (1.0f / mass)) * (-1.0f) && !isDash)
			{
				velocity.y = -45.0f;
				onGround = false;
				stopLeft = false;
				stopRight = false;
			}
			break;
		case GameMessage::RIGHT:
			if (!isDash && !stopRight)
			{
				velocity.x = 20.0f;
				isColliding = false;
			}
			break;
		case GameMessage::RIGHT_DASH:
			isDash = true;
			velocity.x = 40.0f;
			isColliding = false;
			break;
		case GameMessage::LEFT:
			if (!isDash && !stopLeft)
			{
				velocity.x = -20.0f;
				isColliding = false;
			}
			break;
		case GameMessage::LEFT_DASH:
			isDash = true;
			velocity.x = -40.0f;
			isColliding = false;
		case GameMessage::RIGHT_RELEASED:
			if (isDash)
				break;
			if (!isColliding || (lastCollisionVelocity.x > 0 && velocity.x > 0)) velocity.x -= 20.0f;
			if (onGround == true) this->composition->sendMessage(new GameMessage::Message(GameMessage::STAND_ANIMATION));
			break;
		case GameMessage::LEFT_RELEASED:
			if (isDash)
				break;
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
			position.x = (float)composition->getX();
			position.y = (float)composition->getY();
			lastCollisionVelocity = this->velocity;
			this->velocity = collision->velocity;
			this->position += collision->position;
			this->composition->setX(round(position.x));
			this->composition->setY(round(position.y));
			float res = (forces.y * (1.0f / mass)) + gravity.y;
			if (forces.y > 0 && collision->normal.y < 0.0f)
			{
				forces = (gravity / (1.0f / mass)) * (-1.0f);
				if (!onGround) this->composition->sendMessage(new GameMessage::Message(GameMessage::STAND_ANIMATION));
				onGround = true;
			}
			else if (res < 0.0f)
			{
				forces.y = 0.0f;
				onGround = false;
			}

			if (velocity.x == 0.0f) forces.x = 0.0f;
			isColliding = true;


			if (onGround)
			{
				forces = (gravity / (1.0f / mass)) * (-1.0f);
				this->velocity.y = 0.0f;
				stopLeft = false;
				stopRight = false;
			}

			if (collision->normal.x == 1 && onGround)
				stopLeft = true;
			if (collision->normal.x == -1 && onGround)
				stopRight = true;
			break;
		}
	}

	void BodyComponent::Integrate(float dt)
	{
		position.x = (float) composition->getX();
		position.y = (float) composition->getY();

		glm::vec2 newForces = (forces * (1.0f / mass));

		glm::vec2 acceleration = newForces + gravity;
		velocity += acceleration * dt * movementSpeed;

		position += velocity * dt * movementSpeed;

		if (onGround == false && (forces.y <= maxForce)) forces = forces + gravity;

		if (position.y >= 1000.0f)
			this->composition->destroy(true);

		composition->setX(round(position.x));
		composition->setY(round(position.y));

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
	void BodyComponent::setGravity(float intensity)
	{
		gravity = glm::vec2(0.0, intensity);
	}
	void BodyComponent::setForce(glm::vec2 direction, float intensity)
	{
		forces = direction * intensity;
	}
	void BodyComponent::setVelocity(glm::vec2 direction, float intensity)
	{
		velocity = direction * intensity;
	}
	int BodyComponent::getPositionX()
	{
		return (int) position.x;
	}
	int BodyComponent::getPositionY()
	{
		return (int) position.y;
	}
	void BodyComponent::setParentObject(GameObjects::BaseGameObject *parent)
	{
		this->parentObject = parent;
	}
}