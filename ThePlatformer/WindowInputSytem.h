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
		void Update(float dt, std::list<GameObjects::BaseGameObject*>&);
		void Init(void);
		void SendMessage();
	};
}
#endif // !_WINDOWINPUTSYSTEM_H_