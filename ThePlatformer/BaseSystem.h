#pragma once
#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "BaseGameObject.h"
#include <list>

namespace GameSystems
{
	class BaseSystem
	{
	public:
		enum Code {
			Success,
			Error
		};
		virtual int Update(double dt, std::list<GameObjects::BaseGameObject*>&) = 0;
		virtual void Init(std::list<GameObjects::BaseGameObject*>&) = 0;
		virtual void SendAMessage() = 0;
		virtual ~BaseSystem() {}
	};
}

#endif // !_SYSTEM_H_