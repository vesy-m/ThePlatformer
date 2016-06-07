#pragma once
#include <iostream>
#include "BaseGameObject.h"
#include "Message.h"

namespace GameObjects {
	class BaseGameObject;
}

namespace GameComponents {
	enum COMPONENT_TYPE
	{
		WINDOW,
		SPRITE,
		PHYSIC,
		BOX_COLLIDER,
		CIRCLE_COLLIDER,
		COLLIDER,
		DEBUGVECTOR,
		TEXT,
		BUTTON,
		FIRE,
		AIM,
		SOUND,
		ATTACK,
		MECHANIC,
		ELEMENT_SELECTOR,
		CASE_SELECTOR,
		EDITOR_KEYBOARD,
		LIFE_BAR,
		AUTO_PLAY,
		BANNER
	};

	class BaseComponent
	{
	public:
		BaseComponent(GameObjects::BaseGameObject*);
		virtual ~BaseComponent();
		virtual COMPONENT_TYPE getType() const = 0;
		virtual void Update(double) = 0;
		virtual void Init() = 0;
		virtual void sendMessage(GameMessage::Message*) = 0;

		void SetActive(bool);
		bool IsComponentActive();
		GameObjects::BaseGameObject *getComposition(void) const;
	protected:
		bool isActive;
		GameObjects::BaseGameObject *composition;
	};
}
