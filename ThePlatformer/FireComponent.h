#pragma once
#include "BaseGameObject.h"

namespace GameObjects {
	class BaseGameObject;
}

namespace GameComponents {
	class FireComponent : public BaseComponent {
	public:
		FireComponent(GameObjects::BaseGameObject*);
		virtual ~FireComponent();
		virtual COMPONENT_TYPE getType() { return (FIRE); }
		virtual void Update(double) {};
		virtual void Init() = 0;
		virtual void sendMessage(GameMessage::Message*) = 0;
	};
}