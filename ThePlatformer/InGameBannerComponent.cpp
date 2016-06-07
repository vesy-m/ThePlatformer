#include "InGameBannerComponent.h"


namespace GameComponents {

	InGameBannerComponent::InGameBannerComponent(GameObjects::BaseGameObject *object, BannerType type, double time) : BaseComponent(object)
	{
		object->attachComponent(this);
		this->bannerType = type;
		this->time = time;
		this->savedTime = 0;
	}


	InGameBannerComponent::~InGameBannerComponent() { }

	GameObjects::BaseGameObject * InGameBannerComponent::getComposition()
	{
		return this->composition;
	}

	void InGameBannerComponent::Update(double dt)
	{
		this->savedTime += dt;

		if (bannerType == GameComponents::START_GAME && this->savedTime >= this->time / 2) {
			//GameComponents::SpriteComponent *sprite = reinterpret_cast<GameComponents::SpriteComponent*>(getComposition()->getComponent(GameComponents::SPRITE));
			//if (!sprite)
			//	return;
			//sprite->
			GameSystems::ObjectFactory::getInstance().changeGameObjectSpriteComponent(getComposition(), "./assets/sprite/fight.png");
		}

		if (this->savedTime >= this->time)
		{
			std::vector<GameObjects::BaseGameObject *> listPlayers = GameSystems::ObjectFactory::getInstance().getCurrentLevel().getPlayers();
			for (auto player : listPlayers)
			{
				auto component = dynamic_cast<GameComponents::InputComponent*> (player->getComponent(GameComponents::WINDOW));
				if (component) {
					component->SetActive(true);
				}
			}
			getComposition()->destroy(true);
		}
	}

	void InGameBannerComponent::Init() { }

	void InGameBannerComponent::sendMessage(GameMessage::Message *) { }
}
