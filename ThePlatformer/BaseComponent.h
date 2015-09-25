#pragma once
#ifndef _BASECOMPONENT_H_
#define _BASECOMPONENT_H_

#include <iostream>
#include "BaseGameObject.h"
namespace GameObjects {
	class BaseGameObject;
}
namespace GameComponents {
	enum COMPONENT_TYPE
	{
		WINDOW,
		SPRITE,
		LOGIC
	};

	class BaseComponent
	{
	public:
		BaseComponent(GameObjects::BaseGameObject *);
		~BaseComponent();
		virtual COMPONENT_TYPE getType() = 0;
		virtual void Update() = 0;
		virtual void Init() = 0;
	protected:
		GameObjects::BaseGameObject *composition;
	};
}
#endif // !_BASECOMPONENT_H_