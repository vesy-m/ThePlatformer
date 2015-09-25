#pragma once
#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "BaseGameObject.h"
#include <list>

namespace GameSystems
{
	class System
	{
	public:
		enum Code {
			Success,
			Error
		};
		virtual int Update(float dt, std::list<GameObjects::BaseGameObject*>&) = 0;
		virtual void Init(std::list<GameObjects::BaseGameObject*>&) = 0;
		virtual void SendMessage() = 0;
		virtual ~System() {}
	};
}

#endif // !_SYSTEM_H_