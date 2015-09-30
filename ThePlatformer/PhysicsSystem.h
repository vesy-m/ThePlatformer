#pragma once
#ifndef _PHYSICSYSTEM_H_
#define _PHYSICSYSTEM_H_

#include "System.h"

namespace GameSystems {
	class PhysicsSystem : public System
	{
	public:
		PhysicsSystem();
		~PhysicsSystem();
		int Update(double dt, std::list<GameObjects::BaseGameObject*>&);
		void Init(std::list<GameObjects::BaseGameObject*>& listObjects);
		void SendMessage();
	};
}


#endif // !_PHYSICSYSTEM_H_