#pragma once
#ifndef _GRAPHICSSYSTEM_H_
#define _GRAPHICSSYSTEM_H_

#include "System.h"

namespace GameSystems {
	class GraphicsSystem : public System
	{
	public:
		GraphicsSystem();
		~GraphicsSystem();
		int Update(float dt, std::list<GameObjects::BaseGameObject*>&);
		void Init(std::list<GameObjects::BaseGameObject*>& listObjects);
		void SendMessage();
	};
}

#endif // !_GRAPHICSSYSTEM_H_