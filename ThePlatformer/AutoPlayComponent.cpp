#include "AutoPlayComponent.h"


namespace GameComponents {
	AutoPlayComponent::AutoPlayComponent(GameObjects::BaseGameObject *object) : BaseComponent(object)
	{
		object->attachComponent(this);
		this->SetActive(false);

		this->waitingTime = 400;
		this->currentTime = this->waitingTime;
		this->attack_1 = 0;
		this->attack_2 = 0;
		this->attack_3 = 0;
		srand(time(NULL));
	}

	AutoPlayComponent::~AutoPlayComponent()
	{
	}

	GameObjects::BaseGameObject *AutoPlayComponent::getComposition()
	{
		return this->composition;
	}

	void AutoPlayComponent::Update(double dt)
	{
		this->attack_1 = (float)(this->attack_1 - dt > 0 ? this->attack_1 - dt : 0);
		this->attack_2 = (float)(this->attack_2 - dt > 0 ? this->attack_2 - dt : 0);
		this->attack_3 = (float)(this->attack_3 - dt > 0 ? this->attack_3 - dt : 0);

		if (this->currentTime > 0) {
			this->currentTime -= dt;
			return;
		}
		this->currentTime = this->waitingTime;

		GameObjects::BaseGameObject *nearPlayer = getNearPlayer();
		if (nearPlayer == NULL) return;

		GameMessage::MessageId message = GameMessage::DEFAULT;
		
		GameComponents::SpriteComponent *sprite = reinterpret_cast<GameComponents::SpriteComponent*>(getComposition()->getComponent(GameComponents::SPRITE));
		glm::vec2 nearPlayerPosition = glm::vec2(nearPlayer->getX(), nearPlayer->getY());
		glm::vec2 currentPosition = glm::vec2(this->composition->getX(), this->composition->getY());
		glm::vec2 vectorNearPlayer = nearPlayerPosition - currentPosition;
		float distance = glm::length(vectorNearPlayer);


		if (distance >= 250) {
			if ((currentPosition.x < nearPlayerPosition.x))
				message = GameMessage::RIGHT;
			else if ((currentPosition.x > nearPlayerPosition.x))
				message = GameMessage::LEFT;
		}
		else {
			if (((currentPosition.x < nearPlayerPosition.x) && (sprite->revertX)) ||
				((currentPosition.x > nearPlayerPosition.x) && (!sprite->revertX))) {
				sprite->revertX = !sprite->revertX;
			}
			else if (previousMessage == GameMessage::RIGHT)
				message = GameMessage::RIGHT_RELEASED;
			else if (previousMessage == GameMessage::LEFT)
				message = GameMessage::LEFT_RELEASED;
			else if (previousMessage != GameMessage::RIGHT && previousMessage != GameMessage::LEFT) {
				int randAttack = rand() % 20 + 1;
				std::cout << "rand = " << randAttack << std::endl;

				if (randAttack <= 4 && this->attack_3 == 0) {
					message = GameMessage::ATTACK3;
					this->attack_3 = getComposition()->getAttack3Value();
					std::cout << "Attack 3" << std::endl;
				}
				else if (randAttack > 4 && randAttack <= 12 && this->attack_2 == 0) {
					message = GameMessage::ATTACK2;
					this->attack_2 = getComposition()->getAttack2Value();
					std::cout << "Attack 2" << std::endl;
				}
				else {
					message = GameMessage::ATTACK1;
					this->attack_1 = getComposition()->getAttack1Value();
					std::cout << "Attack 1" << std::endl;
				}
			}
		}

		this->previousMessage = message;
		if (message != GameMessage::DEFAULT)
			getComposition()->sendMessage(new GameMessage::Message(message));
	}

	void AutoPlayComponent::Init()
	{
	}

	void AutoPlayComponent::sendMessage(GameMessage::Message *message)
	{
	}

	GameObjects::BaseGameObject * AutoPlayComponent::getNearPlayer()
	{
		std::vector<GameObjects::BaseGameObject *> listPlayers = GameSystems::ObjectFactory::getInstance().getCurrentLevel().getPlayers();
		GameObjects::BaseGameObject *nearPlayer = listPlayers.at(0);

		glm::vec2 currentPosition = glm::vec2(this->composition->getX(), this->composition->getY());
		glm::vec2 currentVectorNearPlayer = glm::vec2(nearPlayer->getX(), nearPlayer->getY()) - currentPosition;

		for (auto player : listPlayers)
		{
			glm::vec2 playerPosition = glm::vec2(player->getX(), player->getY());
			if (playerPosition == currentPosition)
				continue;
			glm::vec2 vectorNearPlayer = playerPosition - currentPosition;
			float l1 = glm::length(currentVectorNearPlayer);
			float l2 = glm::length(vectorNearPlayer);

			if (l1 > l2 || l1 == 0)
			{
				nearPlayer = player;
				currentVectorNearPlayer = vectorNearPlayer;
			}
		}

		return nearPlayer;
	}

}
