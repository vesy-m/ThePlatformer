#include <iostream>
#include "GameEngine.h"
#include "System.h"

namespace GameEngine {
	Core::Core() {
	}

	Core::~Core() {
		for (auto it = this->m_systems.begin(); it != this->m_systems.end(); ++it)
			delete *it;
	}
	
	void Core::Init(void) {
		for each (GameSystems::System* system in this->m_systems)
			system->Init();
	}

	void Core::Update(float dt) {
		//for (unsigned ínt i = 0; i < this->m_systems.size(); ++i)
		//	this->m_systems[i].Update(dt, ObjectFactory->GetObjectList());
	}

	void Core::MainLoop(void) {
		while (42) {
			for each (GameSystems::System *system in this->m_systems)
				system->Update(DT, this->m_objects);
		}
	}

	void Core::Add(GameObjects::BaseGameObject *object) {
		this->m_objects.push_back(object);
	}

	void Core::Add(GameSystems::System *sys) {
		this->m_systems.push_back(sys);
	}
}