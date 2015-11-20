#pragma once

#include "FireComponent.h"
#include "Message.h"
#include "ObjectFactory.h"

namespace GameSystems {
	class ObjectFactory;
}

namespace GameMessages {
	class Message;
}

namespace GameObjects {
	class BaseGameObject;
}

namespace GameComponents {
	class FireBallComponent : public FireComponent {
		friend class GameSystems::ObjectFactory;
	private:
		FireBallComponent(GameObjects::BaseGameObject*);
	public:
		virtual ~FireBallComponent();
		virtual void Init(void);
		virtual void sendMessage(GameMessage::Message*);
	};
}