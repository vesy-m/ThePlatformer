#pragma once

#include "BaseSystem.h"

namespace GameSystems {
	class PhysicsSystem : public BaseSystem
	{
	public:
		PhysicsSystem();
		~PhysicsSystem();
		int Update(double dt, std::list<GameObjects::BaseGameObject*>&);
		void Init(std::list<GameObjects::BaseGameObject*>&);
		void SendAMessage();
	};
}