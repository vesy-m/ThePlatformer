#include "BaseballAttack.h"
#include "BodyComponent.h"
#include "BoxCollider.h"
#include "TimerComponent.h"
#include "VectorDebugComponent.h"


namespace GameComponents {
	BaseballAttack::BaseballAttack(GameObjects::BaseGameObject *object) : CAAttackComponent(object)
	{
	}


	BaseballAttack::~BaseballAttack()
	{
	}
	void BaseballAttack::Init()
	{
		isAtt3 = false;
	}

	void BaseballAttack::sendMessage(GameMessage::Message *message)
	{
		GameComponents::InputComponent *input = reinterpret_cast<GameComponents::InputComponent*> (this->composition->getComponent(GameComponents::WINDOW));
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
		case GameMessage::ATTACK3_RELEASED:
			Attack3Released();
			break;
		default:
			break;
		}
	}
	void BaseballAttack::Attack1()
	{
		int centerX = (this->getComposition()->getX() + (this->getComposition()->getWidth() / 2));
		int centerY = (this->getComposition()->getY() + (this->getComposition()->getHeight() / 2));
		GameComponents::SpriteComponent *sprite = reinterpret_cast<GameComponents::SpriteComponent*>(getComposition()->getComponent(GameComponents::SPRITE));

		glm::vec2 direction = glm::vec2(100.0, 100.0);
		if (sprite->revertX) direction = glm::vec2((-100 + centerX) - centerX, (-70 + centerY) - centerY);
		else direction = glm::vec2((100 + centerX) - centerX, (-70 + centerY) - centerY);

		//GameObjects::BaseGameObject *arrow = GameSystems::ObjectFactory::getInstance().createProjectile(getComposition(), getComposition()->getX(),
		//	getComposition()->getY(), /*this->getDuration()*/ 1.0f, glm::normalize(direction), GameSystems::ObjectFactory::SOCCER_BALL);
		//GameObjects::BaseGameObject *arrow = GameSystems::ObjectFactory::getInstance().createProjectile(createProjectile(getComposition(), ATTACK1, 1.0f, glm::normalize(direction)), getComposition()->getX(),
		//	getComposition()->getY(), 1.0f, glm::normalize(direction), "./assets/sprite/tennis_ball.png", true);

		createProjectile(getComposition(), GameObjects::BASE_BALL, 1.0f, glm::normalize(direction), "./assets/sprite/baseball.png");
		this->composition->sendMessage(new GameMessage::Message(GameMessage::BASEBALL_SHOOT));
	}

	void BaseballAttack::Attack2()
	{
		int centerX = (this->getComposition()->getX() + (this->getComposition()->getWidth() / 2));
		int centerY = (this->getComposition()->getY() + (this->getComposition()->getHeight() / 2));
		GameComponents::SpriteComponent *sprite = reinterpret_cast<GameComponents::SpriteComponent*>(getComposition()->getComponent(GameComponents::SPRITE));

		glm::vec2 direction = glm::vec2(100.0, 0.0);
		if (sprite->revertX) direction = glm::vec2((-100 + centerX) - centerX, (centerY) - centerY);
		else direction = glm::vec2((100 + centerX) - centerX, (centerY) - centerY);
		revert = sprite->revertX;

		//GameObjects::BaseGameObject *arrow = GameSystems::ObjectFactory::getInstance().createProjectile(getComposition(), getComposition()->getX(),
		//	getComposition()->getY(), /*this->getDuration()*/ 1.0f, glm::normalize(direction), GameSystems::ObjectFactory::SOCCER_BALL);
		/*GameObjects::BaseGameObject *arrow = GameSystems::ObjectFactory::getInstance().createProjectile(createProjectile(getComposition(), ATTACK1, 1.0f, glm::normalize(direction)), getComposition()->getX(),
			getComposition()->getY(), 1.0f, glm::normalize(direction), "./assets/sprite/bat.png", false);*/

		createProjectile(getComposition(), GameObjects::BAT, 1.0f, glm::normalize(direction), "./assets/sprite/bat.png");
	}

	void BaseballAttack::Attack3()
	{
		if (isAtt3)
			return;
		if (this->composition->getInvicible()) return;
		GameComponents::TimerComponent *timer = reinterpret_cast<GameComponents::TimerComponent*>(getComposition()->getComponent(GameComponents::MECHANIC));
		if (!timer) timer = new GameComponents::TimerComponent(this->composition);
		timer->Init();
		timer->setTimerType(GameObjects::BLOCK);
		timer->setTime(1000);
		this->composition->setInvicible(true);
		this->composition->sendMessage(new GameMessage::Message(GameMessage::BLOCK));
		timer->startTimer();
		isAtt3 = true;
	}

	void BaseballAttack::Attack3Released()
	{
		GameComponents::TimerComponent *timer = reinterpret_cast<GameComponents::TimerComponent*>(getComposition()->getComponent(GameComponents::MECHANIC));
		assert(timer != NULL);
		timer->stopTimer();
		this->composition->setInvicible(false);
		this->composition->sendMessage(new GameMessage::Message(GameMessage::STOP_BLOCK));
		isAtt3 = false;
	}

	GameObjects::BaseGameObject *BaseballAttack::createProjectile(GameObjects::BaseGameObject *shooter, GameObjects::ProjectileType const type, float base_force, glm::vec2 direction, std::string spriteStr)
	{
		GameObjects::BaseGameObject *projectile = NULL;/*GameSystems::ObjectFactory::getInstance().getUsableProjectile(type);*/
		GameComponents::BodyComponent *body = NULL;
		GameComponents::SpriteComponent *sprite = NULL;
		GameComponents::TimerComponent *timer = NULL;

		if (projectile) {
			body = dynamic_cast<GameComponents::BodyComponent*>(projectile->getComponent(GameComponents::PHYSIC));
		}
		else {
			projectile = new GameObjects::BaseGameObject();
			assert(projectile != NULL);
			sprite = new GameComponents::SpriteComponent(projectile, spriteStr);
			new GameComponents::BoxCollider(projectile);
			new GameComponents::VectorDebugComponent(projectile, "square");
			body = new GameComponents::BodyComponent(projectile);

			if (direction.x <= 0)
				sprite->revertX = true;
			projectile->setName(shooter->getName());
			projectile->setDepth(0);
			projectile->setType(GameObjects::objectType::PROJECTILE);
			projectile->setProjectileType(type);
			switch (type)
			{
			case GameObjects::BASE_BALL:
				projectile->setBounce(0.3f);
				projectile->setMass(25.0f);
				projectile->setHeight(int(30 * 0.50f));
				projectile->setWidth(int(30 * 0.50f));
				projectile->setScale(0.05f);
				projectile->setPower(10);
				projectile->setX(shooter->getX() + (shooter->getWidth() / 2));
				projectile->setY(shooter->getY() + (shooter->getHeight() / 2) - 10);
				break;
			case GameObjects::BAT:
				projectile->setBounce(0.3f);
				projectile->setMass(25.0f);
				projectile->setHeight(int(30 * 0.50f));
				projectile->setWidth(int(110 * 0.50f));
				projectile->setScale(0.3f);
				projectile->setPower(30);
				if (revert)
					projectile->setX(shooter->getX() - (shooter->getWidth()));
				else
					projectile->setX(shooter->getX() + (shooter->getWidth() / 2));
				projectile->setY(shooter->getY() + (shooter->getHeight() / 2) - 10);
				break;
			case GameObjects::BLOCK:
				projectile->setBounce(0.3f);
				projectile->setX(shooter->getX());
				projectile->setY(shooter->getY());
				break;
			default:
				break;
			}
		}
		projectile->Init();
		assert(body != NULL);
		body->Init(base_force, direction);
		if (type == GameObjects::BAT)
		{
			timer = new GameComponents::TimerComponent(projectile);
			timer->setTimerType(type);
			timer->setTime(450);
			timer->startTimer();
			body->setGravity(0.0f);
		}
		GameSystems::ObjectFactory::getInstance().createProjectile(projectile);
		return projectile;
	}
}
