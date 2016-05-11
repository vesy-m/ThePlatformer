#include "TennisAttack.h"
#include "BodyComponent.h"
#include "BoxCollider.h"
#include "VectorDebugComponent.h"

namespace GameComponents
{
	TennisAttack::TennisAttack(GameObjects::BaseGameObject *object) : CAAttackComponent(object)
	{
	}

	TennisAttack::~TennisAttack() {}

	void TennisAttack::Init() {}

	void TennisAttack::sendMessage(GameMessage::Message *message)
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

	void TennisAttack::Attack1()
	{
		int centerX = (this->getComposition()->getX() + (this->getComposition()->getWidth() / 2));
		int centerY = (this->getComposition()->getY() + (this->getComposition()->getHeight() / 2));
		GameComponents::SpriteComponent *sprite = reinterpret_cast<GameComponents::SpriteComponent*>(getComposition()->getComponent(GameComponents::SPRITE));

		glm::vec2 direction = glm::vec2(100.0, 100.0);
		if (sprite->revertX) direction = glm::vec2((-80 + centerX) - centerX, (-40 + centerY) - centerY);
		else direction = glm::vec2((80 + centerX) - centerX, (-40 + centerY) - centerY);

		createProjectile(getComposition(), GameObjects::TENNIS_BALL1, 1.0f, glm::normalize(direction), "./assets/sprite/tennisball.png");
		this->composition->sendMessage(new GameMessage::Message(GameMessage::BASEBALL_SHOOT));
	}

	void TennisAttack::Attack2()
	{
		int centerX = (this->getComposition()->getX() + (this->getComposition()->getWidth() / 2));
		int centerY = (this->getComposition()->getY() + (this->getComposition()->getHeight() / 2));
		GameComponents::SpriteComponent *sprite = reinterpret_cast<GameComponents::SpriteComponent*>(getComposition()->getComponent(GameComponents::SPRITE));

		glm::vec2 direction = glm::vec2(100.0, 100.0);
		if (sprite->revertX) direction = glm::vec2((-100 + centerX) - centerX, (centerY) - centerY);
		else direction = glm::vec2((100 + centerX) - centerX, (centerY) - centerY);

		createProjectile(getComposition(), GameObjects::TENNIS_BALL2, 1.0f, glm::normalize(direction), "./assets/sprite/tennisball.png");
		this->composition->sendMessage(new GameMessage::Message(GameMessage::BASEBALL_SHOOT));
	}

	void TennisAttack::Attack3()
	{

		int centerX = (this->getComposition()->getX() + (this->getComposition()->getWidth() / 2));
		int centerY = (this->getComposition()->getY() + (this->getComposition()->getHeight() / 2));
		GameComponents::SpriteComponent *sprite = reinterpret_cast<GameComponents::SpriteComponent*>(getComposition()->getComponent(GameComponents::SPRITE));

		glm::vec2 direction = glm::vec2(100.0, 100.0);
		if (sprite->revertX) direction = glm::vec2((-100 + centerX) - centerX, (-70 + centerY) - centerY);
		else direction = glm::vec2((100 + centerX) - centerX, (-70 + centerY) - centerY);

		//glm::vec2 direction = glm::vec2(100.0, 100.0);
		//if (sprite->revertX) direction = glm::vec2((-100 + centerX) - centerX, (centerY) - centerY);
		//else direction = glm::vec2((100 + centerX) - centerX, (centerY) - centerY);

		createProjectile(getComposition(), GameObjects::TENNIS_BREAK, 1.0f, glm::normalize(direction), "./assets/sprite/tennisballRed.png");
		this->composition->sendMessage(new GameMessage::Message(GameMessage::BASEBALL_SHOOT));
	}

	GameObjects::BaseGameObject *TennisAttack::createProjectile(GameObjects::BaseGameObject *shooter, GameObjects::ProjectileType const type, float base_force, glm::vec2 direction, std::string spriteStr)
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
			case GameObjects::TENNIS_BALL1:
				projectile->setBounce(0.3f);
				projectile->setMass(25.0f);
				projectile->setHeight(int(30 * 0.50f));
				projectile->setWidth(int(30 * 0.50f));
				projectile->setScale(0.03f);
				projectile->setPower(15);
				projectile->setX(shooter->getX() + (shooter->getWidth() / 2));
				projectile->setY(shooter->getY() + (shooter->getHeight() / 2) - 10);
				break;
			case GameObjects::TENNIS_BALL2:
				projectile->setBounce(0.3f);
				projectile->setBounce(0.3f);
				projectile->setMass(25.0f);
				projectile->setHeight(int(30 * 0.50f));
				projectile->setWidth(int(30 * 0.50f));
				projectile->setScale(0.03f);
				projectile->setPower(3);
				projectile->setX(shooter->getX() + (shooter->getWidth() / 2));
				projectile->setY(shooter->getY() + (shooter->getHeight() / 2) - 10);
				break;
			case GameObjects::TENNIS_BREAK:
				projectile->setBounce(0.3f);
				projectile->setBounce(0.3f);
				projectile->setMass(25.0f);
				projectile->setHeight(int(30 * 0.50f));
				projectile->setWidth(int(30 * 0.50f));
				projectile->setScale(0.1f);
				projectile->setPower(35);
				projectile->setX(shooter->getX() + (shooter->getWidth() / 2));
				projectile->setY(shooter->getY() + (shooter->getHeight() / 2) - 10);
				projectile->setType(GameObjects::objectType::PROJECTILE_BREAK);
				break;
			default:
				break;
			}
		}
		projectile->Init();
		assert(body != NULL);
		body->Init(base_force, direction);
		if (type == GameObjects::TENNIS_BALL2)
			body->setGravity(1.0f);
		if (type == GameObjects::TENNIS_BREAK)
			body->setGravity(0.0f);
		GameSystems::ObjectFactory::getInstance().createProjectile(projectile);
		return projectile;
	}
}
