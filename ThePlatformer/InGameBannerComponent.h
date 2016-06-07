#pragma once
#include "BaseGameObject.h"
#include "Message.h"
#include "ObjectFactory.h"
#include "InputComponent.h"

namespace GameComponents {

	enum BannerType {
		START_GAME,
		END_ROUND
	};
	class InGameBannerComponent : public BaseComponent
	{
	public:
		InGameBannerComponent(GameObjects::BaseGameObject*, BannerType, double);
		~InGameBannerComponent();

		COMPONENT_TYPE getType() const { return AUTO_PLAY; }
		GameObjects::BaseGameObject *getComposition();
		void Update(double);

		void Init();
		void sendMessage(GameMessage::Message*);

	private:
		BannerType bannerType;
		double time;
		double savedTime;
	};
}

