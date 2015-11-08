#pragma once
#ifndef _BASECOMPONENT_H_
#define _BASECOMPONENT_H_

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
		LOGIC,
		PHYSIC,
		COLLIDER,
		DEBUGVECTOR,
		TEXT,
		BUTTON
	};

	class BaseComponent
	{
	public:
		BaseComponent();
		BaseComponent(GameObjects::BaseGameObject *);
		~BaseComponent();
		virtual COMPONENT_TYPE getType() = 0;
		virtual void Update(double) = 0;
		virtual void Init() = 0;
		virtual void sendMessage(GameMessage::Message*) = 0;
	public:

		GameObjects::BaseGameObject *composition;
	};
}
#endif // !_BASECOMPONENT_H_