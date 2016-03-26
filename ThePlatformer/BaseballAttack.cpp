#include "BaseballAttack.h"
#include "BodyComponent.h"
#include "BoxCollider.h"
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
	}
	void BaseballAttack::sendMessage(GameMessage::Message *message)
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
		GameObjects::BaseGameObject *arrow = GameSystems::ObjectFactory::getInstance().createProjectile(createProjectile(getComposition(), ATTACK1), getComposition()->getX(),
			getComposition()->getY(), /*this->getDuration()*/ 1.0f, glm::normalize(direction), "./assets/sprite/tennis_ball.png");
	}

	void BaseballAttack::Attack2()
	{
		int centerX = (this->getComposition()->getX() + (this->getComposition()->getWidth() / 2));
		int centerY = (this->getComposition()->getY() + (this->getComposition()->getHeight() / 2));
		GameComponents::SpriteComponent *sprite = reinterpret_cast<GameComponents::SpriteComponent*>(getComposition()->getComponent(GameComponents::SPRITE));

		glm::vec2 direction = glm::vec2(100.0, 0.0);
		if (sprite->revertX) direction = glm::vec2((-100 + centerX) - centerX, (centerY) - centerY);
		else direction = glm::vec2((100 + centerX) - centerX, (centerY) - centerY);

		//GameObjects::BaseGameObject *arrow = GameSystems::ObjectFactory::getInstance().createProjectile(getComposition(), getComposition()->getX(),
		//	getComposition()->getY(), /*this->getDuration()*/ 1.0f, glm::normalize(direction), GameSystems::ObjectFactory::SOCCER_BALL);
		GameObjects::BaseGameObject *arrow = GameSystems::ObjectFactory::getInstance().createProjectile(createProjectile(getComposition(), ATTACK1), getComposition()->getX(),
			getComposition()->getY(), /*this->getDuration()*/ 1.0f, glm::normalize(direction), "./assets/sprite/tennis_ball.png");
	}

	void BaseballAttack::Attack3()
	{
	}

	GameObjects::BaseGameObject *BaseballAttack::createProjectile(GameObjects::BaseGameObject *shooter, Attack const type)
	{
		GameObjects::BaseGameObject *projectile = NULL;

		projectile = new GameObjects::BaseGameObject();
		projectile->setName(shooter->getName());
		projectile->setDepth(0);
		projectile->setType(GameObjects::objectType::PROJECTILE);
		switch (type)
		{
		case ATTACK1:
			projectile->setBounce(0.3f);
			projectile->setMass(25.0f);
			shooter->setCooldown(1500.0f); // A changer
			projectile->setHeight(int(30 * 0.50f));
			projectile->setWidth(int(30 * 0.50f));
			projectile->setScale(0.50f);
			projectile->setPower(20);
			break;
		case ATTACK2:
			projectile->setBounce(0.3f);
			projectile->setBounce(0.3f);
			projectile->setMass(25.0f);
			shooter->setCooldown(1500.0f); // A changer
			projectile->setHeight(int(30 * 0.50f));
			projectile->setWidth(int(30 * 0.50f));
			projectile->setScale(0.50f);
			projectile->setPower(20);
			break;
		case ATTACK3:
			projectile->setBounce(0.3f);
			break;
		default:
			break;
		}
		return projectile;
	}
}
