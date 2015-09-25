#pragma once
#ifndef _WINDOWINPUTSYSTEM_H_
#define _WINDOWINPUTSYSTEM_H_

#include "System.h"

namespace GameSystems {
	class WindowInputSytem : public System
	{
	public:
		WindowInputSytem();
		~WindowInputSytem();
		int Update(float dt, std::list<GameObjects::BaseGameObject*>&);
		void Init(std::list<GameObjects::BaseGameObject*>& listObjects);
		void SendMessage();
	};
}
#endif // !_WINDOWINPUTSYSTEM_H_