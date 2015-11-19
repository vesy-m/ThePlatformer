#pragma once

#include "FireComponent.h"
#include "Message.h"

namespace GameMessages {
	class Message;
}

namespace GameObjects {
	class BaseGameObject;
}

namespace GameComponents {
	class FireBallComponent : public FireComponent {
	public:
		FireBallComponent(GameObjects::BaseGameObject*);
		virtual ~FireBallComponent();
		virtual void Init(void);
		virtual void sendMessage(GameMessage::Message*);
	};
}