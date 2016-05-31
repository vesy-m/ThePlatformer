#include "RugbyManAttack.h"
#include "BodyComponent.h"
#include "BoxCollider.h"
#include "TimerComponent.h"
#include "VectorDebugComponent.h"

namespace GameComponents
{
	RugbyManAttack::RugbyManAttack(GameObjects::BaseGameObject *object) : CAAttackComponent(object)
	{
	}

	RugbyManAttack::~RugbyManAttack() {}

	void RugbyManAttack::Init() {}

	void RugbyManAttack::sendMessage(GameMessage::Message *message)
	{
		switch (message->id)
		{
		case GameMessage::ATTACK1:
			Attack1();
			break;
		case GameMessage::ATTACK2:
			Attack2();
			break;
		case GameMessage::ATTACK3:
			Attack3();
			break;
		case GameMessage::STOP_DASH:
			this->composition->setType(GameObjects::PLAYER);
		default:
			break;
		}
	}

	void RugbyManAttack::Attack1()
	{
		int centerX = (this->getComposition()->getX() + (this->getComposition()->getWidth() / 2));
		int centerY = (this->getComposition()->getY() + (this->getComposition()->getHeight() / 2));
		GameComponents::SpriteComponent *sprite = reinterpret_cast<GameComponents::SpriteComponent*>(getComposition()->getComponent(GameComponents::SPRITE));

		glm::vec2 direction = glm::vec2(100.0, 0.0);
		if (sprite->revertX) direction = glm::vec2((-100 + centerX) - centerX, (centerY)-centerY);
		else direction = glm::vec2((100 + centerX) - centerX, (centerY)-centerY);

		createProjectile(getComposition(), GameObjects::RUGBY_BALL, 1.0f, glm::normalize(direction), "./assets/sprite/rugby_ball.png");
		this->composition->sendMessage(new GameMessage::Message(GameMessage::BASEBALL_SHOOT));
	}

	void RugbyManAttack::Attack2()
	{
		int centerX = (this->getComposition()->getX() + (this->getComposition()->getWidth() / 2));
		int centerY = (this->getComposition()->getY() + (this->getComposition()->getHeight() / 2));
		GameComponents::SpriteComponent *sprite = reinterpret_cast<GameComponents::SpriteComponent*>(getComposition()->getComponent(GameComponents::SPRITE));

		glm::vec2 direction = glm::vec2(100.0, 100.0);
		if (sprite->revertX) direction = glm::vec2((-60 + centerX) - centerX, (-40 + centerY) - centerY);
		else direction = glm::vec2((60 + centerX) - centerX, (-40 + centerY) - centerY);

		createProjectile(getComposition(), GameObjects::DROP, 1.0f, glm::normalize(direction), "./assets/sprite/rugby_ball.png");
		this->composition->sendMessage(new GameMessage::Message(GameMessage::BASEBALL_SHOOT));
	}

	void RugbyManAttack::Attack3()
	{
		GameComponents::SpriteComponent *sprite = reinterpret_cast<GameComponents::SpriteComponent*>(getComposition()->getComponent(GameComponents::SPRITE));
		if (sprite->revertX)
			this->composition->sendMessage(new GameMessage::Message(GameMessage::LEFT_DASH));
		else
			this->composition->sendMessage(new GameMessage::Message(GameMessage::RIGHT_DASH));
		this->composition->setType(GameObjects::PLAYER_ATTACK);
		this->composition->setPower(30);
		GameComponents::TimerComponent *timer = reinterpret_cast<GameComponents::TimerComponent*>(getComposition()->getComponent(GameComponents::MECHANIC));
		if (!timer)
			timer = new GameComponents::TimerComponent(this->composition);
		timer->Init();
		timer->setTimerType(GameObjects::DASH);
		timer->setTime(350);
		timer->startTimer();
	}

	GameObjects::BaseGameObject * RugbyManAttack::createProjectile(GameObjects::BaseGameObject *shooter, GameObjects::ProjectileType const type, float base_force, glm::vec2 direction, std::string sprite)
	{
		GameObjects::BaseGameObject *projectile = NULL;
		GameComponents::BodyComponent *body = NULL;
		GameComponents::TimerComponent *timer = NULL;

		if (projectile) {
			body = dynamic_cast<GameComponents::BodyComponent*>(projectile->getComponent(GameComponents::PHYSIC));
		}
		else
		{
			projectile = new GameObjects::BaseGameObject();
			assert(projectile != NULL);
			new GameComponents::SpriteComponent(projectile, sprite);
			new GameComponents::BoxCollider(projectile);
			new GameComponents::VectorDebugComponent(projectile, "square");
			body = new GameComponents::BodyComponent(projectile);

			projectile->setName(shooter->getName());
			projectile->setDepth(0);
			projectile->setType(GameObjects::objectType::PROJECTILE);
			projectile->setProjectileType(type);
			switch (type)
			{
			case GameObjects::RUGBY_BALL:
				projectile->setBounce(0.3f);
				projectile->setMass(25.0f);
				projectile->setHeight(int(30 * 0.50f));
				projectile->setWidth(int(30 * 0.50f));
				projectile->setScale(0.035f);
				projectile->setPower(10);
				break;
			case GameObjects::DROP:
				projectile->setBounce(0.3f);
				projectile->setMass(25.0f);
				projectile->setHeight(int(30 * 0.50f));
				projectile->setWidth(int(30 * 0.50f));
				projectile->setScale(0.035);
				projectile->setPower(25);
				break;
			case GameObjects::DASH:
				projectile->setBounce(0.3f);

				break;
			default:
				break;
			}
		}
		projectile->setX(shooter->getX() + (shooter->getWidth() / 2) - 10);
		projectile->setY(shooter->getY() + (shooter->getHeight() / 2) - 10);
		projectile->Init();
		assert(body != NULL);
		body->Init(base_force, direction);
		body->setGravity(4.0f);
		if (type == GameObjects::RUGBY_BALL)
		{
			timer = new GameComponents::TimerComponent(projectile);
			timer->setTimerType(type);
			timer->setTime(450);
			timer->startTimer();
		}
		if (type == GameObjects::DROP)
		{
			timer = new GameComponents::TimerComponent(projectile);
			timer->setTimerType(type);
			timer->setTime(450);
			timer->startTimer();
		}
		GameSystems::ObjectFactory::getInstance().createProjectile(projectile);
		return projectile;
	}
}