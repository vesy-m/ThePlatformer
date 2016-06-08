#include "BoxerAttack.h"
#include "BodyComponent.h"
#include "BoxCollider.h"
#include "TimerComponent.h"
#include "VectorDebugComponent.h"


namespace GameComponents {
	BoxerAttack::BoxerAttack(GameObjects::BaseGameObject *object) : CAAttackComponent(object)
	{
	}


	BoxerAttack::~BoxerAttack() { }

	void BoxerAttack::Init() { }

	void BoxerAttack::sendMessage(GameMessage::Message *message)
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

	void BoxerAttack::Attack1()
	{
		int centerX = (this->getComposition()->getX() + (this->getComposition()->getWidth() / 2));
		int centerY = (this->getComposition()->getY() + (this->getComposition()->getHeight() / 2));
		GameComponents::SpriteComponent *sprite = reinterpret_cast<GameComponents::SpriteComponent*>(getComposition()->getComponent(GameComponents::SPRITE));

		glm::vec2 direction = glm::vec2(100.0, 100.0);
		if (sprite->revertX) direction = glm::vec2((-100 + centerX) - centerX, (centerY)-centerY);
		else direction = glm::vec2((100 + centerX) - centerX, (centerY)-centerY);

		createProjectile(getComposition(), GameObjects::PUNCH, 0.0f, glm::normalize(direction), "");
		this->composition->sendMessage(new GameMessage::Message(GameMessage::PUNCH_LEFT));
	}

	void BoxerAttack::Attack2()
	{
		int centerX = (this->getComposition()->getX() + (this->getComposition()->getWidth() / 2));
		int centerY = (this->getComposition()->getY() + (this->getComposition()->getHeight() / 2));
		GameComponents::SpriteComponent *sprite = reinterpret_cast<GameComponents::SpriteComponent*>(getComposition()->getComponent(GameComponents::SPRITE));

		glm::vec2 direction = glm::vec2(100.0, 100.0);
		if (sprite->revertX) direction = glm::vec2((-100 + centerX) - centerX, (centerY)-centerY);
		else direction = glm::vec2((100 + centerX) - centerX, (centerY)-centerY);

		createProjectile(getComposition(), GameObjects::SPECIAL_PUNCH, 1.0f, glm::normalize(direction), "./assets/sprite/boxingGlove.png");
		this->composition->sendMessage(new GameMessage::Message(GameMessage::PUNCH_RIGHT));
	}

	void BoxerAttack::Attack3()
	{
		glm::vec2 direction = glm::vec2(0.0, 0.0);

		GameComponents::TimerComponent *timer = reinterpret_cast<GameComponents::TimerComponent*>(getComposition()->getComponent(GameComponents::MECHANIC));
		if (!timer)
			timer = new GameComponents::TimerComponent(this->composition);
		timer->Init();
		timer->setTimerType(GameObjects::BOXER_POWERUP);
		timer->setTime(4000);
		timer->startTimer();

		this->composition->setPowerupDefense(1.5);
		this->composition->setPowerupDamage(1.5);

		createProjectile(getComposition(), GameObjects::BOXER_POWERUP_AURA, 0.0f, glm::normalize(direction), "./config/sprite_sheets/desc-aura.json");
		//this->composition->sendMessage(new GameMessage::Message(GameMessage::PUNCH_RIGHT));
	}

	GameObjects::BaseGameObject * BoxerAttack::createProjectile(GameObjects::BaseGameObject *shooter, GameObjects::ProjectileType const type, float base_force, glm::vec2 direction, std::string spriteStr)
	{
		GameObjects::BaseGameObject *projectile = NULL;
		GameComponents::BodyComponent *body = NULL;
		GameComponents::SpriteComponent *sprite = NULL;
		GameComponents::TimerComponent *timer = NULL;

		if (projectile) {
			body = dynamic_cast<GameComponents::BodyComponent*>(projectile->getComponent(GameComponents::PHYSIC));
		}
		else {
			projectile = new GameObjects::BaseGameObject();
			assert(projectile != NULL);
			if (!spriteStr.empty())
				sprite = new GameComponents::SpriteComponent(projectile, spriteStr);
			if (type != GameObjects::BOXER_POWERUP_AURA)
				new GameComponents::BoxCollider(projectile);
			new GameComponents::VectorDebugComponent(projectile, "square");
			body = new GameComponents::BodyComponent(projectile);

			if (direction.x < 0 && sprite)
				sprite->revertX = true;
			projectile->setName(shooter->getName());
			projectile->setDepth(0);
			projectile->setType(GameObjects::objectType::PROJECTILE);
			projectile->setProjectileType(type);
			switch (type)
			{
			case GameObjects::PUNCH:
				projectile->setBounce(0.0f);
				projectile->setMass(25.0f);
				projectile->setHeight(int(30 * 0.50f));
				projectile->setWidth(int(60 * 0.50f));
				projectile->setScale(0.0f);
				projectile->setPower((int)std::round(18 * (float)this->composition->getPowerupDamage()));
				if (direction.x <= 0)
					projectile->setX(shooter->getX() - (shooter->getWidth() / 2));
				else if (direction.x > 0)
					projectile->setX(shooter->getX() + (shooter->getWidth() / 2) + 5);
				projectile->setY(shooter->getY() + (shooter->getHeight() / 2) - 15);
				break;
			case GameObjects::SPECIAL_PUNCH:
				projectile->setBounce(0.0f);
				projectile->setMass(25.0f);
				projectile->setHeight(int(40 * 0.50f));
				projectile->setWidth(int(40 * 0.50f));
				projectile->setScale(0.25f);
				projectile->setPower((int)std::round(12 * (float)this->composition->getPowerupDamage()));
				if (direction.x <= 0)
					projectile->setX(shooter->getX() - (shooter->getWidth() / 2));
				else if (direction.x > 0)
					projectile->setX(shooter->getX() + (shooter->getWidth() / 2));
				projectile->setY(shooter->getY() + (shooter->getHeight() / 2) - 10);
				break;
			case GameObjects::BOXER_POWERUP_AURA:
				projectile->setBounce(0.0f);
				projectile->setMass(25.0f);
				projectile->setHeight(int(50));
				projectile->setWidth(int(30));
				projectile->setScale(1.0f);
				projectile->setPower(10 * this->composition->getPowerupDamage());
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
		if (type == GameObjects::PUNCH)
		{
			timer = new GameComponents::TimerComponent(projectile);
			timer->setTimerType(type);
			timer->setTime(100);
			timer->startTimer();
			body->setGravity(0.0f);
			body->setParentObject(this->getComposition());
		}
		if (type == GameObjects::SPECIAL_PUNCH)
		{
			timer = new GameComponents::TimerComponent(projectile);
			timer->setTimerType(type);
			timer->setTime(300);
			timer->startTimer();
			body->setGravity(0.0f);
		}
		if (type == GameObjects::BOXER_POWERUP_AURA)
		{
			timer = new GameComponents::TimerComponent(projectile);
			timer->setTimerType(type);
			timer->setTime(4000);
			timer->startTimer();
			body->setGravity(0.0f);
			body->setParentObject(this->getComposition());
		}
		GameSystems::ObjectFactory::getInstance().createProjectile(projectile);
		return projectile;
	}
}
