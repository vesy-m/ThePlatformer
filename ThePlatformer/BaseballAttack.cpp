#include "BaseballAttack.h"


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
	void BaseballAttack::sendMessage(GameMessage::Message *)
	{
	}
	void BaseballAttack::Attack1()
	{
		int centerX = (this->getComposition()->getX() + (this->getComposition()->getWidth() / 2));
		int centerY = (this->getComposition()->getY() + (this->getComposition()->getHeight() / 2));
		GameComponents::SpriteComponent *sprite = reinterpret_cast<GameComponents::SpriteComponent*>(getComposition()->getComponent(GameComponents::SPRITE));

		glm::vec2 direction = glm::vec2(100.0, 100.0);
		if (sprite->revertX) direction = glm::vec2((-100 + centerX) - centerX, (-70 + centerY) - centerY);
		else direction = glm::vec2((100 + centerX) - centerX, (-70 + centerY) - centerY);

		GameObjects::BaseGameObject *arrow = GameSystems::ObjectFactory::getInstance().createProjectile(getComposition(), getComposition()->getX(),
			getComposition()->getY(), /*this->getDuration()*/ 1.0f, glm::normalize(direction), GameSystems::ObjectFactory::SOCCER_BALL);
	}
	void BaseballAttack::Attack2()
	{
	}
	void BaseballAttack::Attack3()
	{
	}
}
