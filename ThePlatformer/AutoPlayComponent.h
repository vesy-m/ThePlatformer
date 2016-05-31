#pragma once
#include <stdlib.h>
#include <time.h>

#include "BaseGameObject.h"
#include "Message.h"
#include "ObjectFactory.h"
#include "Singleton.h"



namespace GameComponents {

	class AutoPlayComponent : public BaseComponent
	{
	public:
		AutoPlayComponent(GameObjects::BaseGameObject *);
		~AutoPlayComponent();

		COMPONENT_TYPE getType() const { return AUTO_PLAY; }
		GameObjects::BaseGameObject *getComposition();
		void Update(double);

		void Init();
		void sendMessage(GameMessage::Message*);


	private:
		GameObjects::BaseGameObject *getNearPlayer();

		double waitingTime;
		double currentTime;

		float attack_1;
		float attack_2;
		float attack_3;
		
		GameMessage::MessageId previousMessage;
	};
}

