#include <iostream>
#include "GameEngine.h"
#include "System.h"

namespace GameEngine {
	Core::Core() {
	}

	Core::~Core() {
		auto it = this->m_systems.begin();
		for (it = it; it != this->m_systems.end(); ++it)
			delete *it;
	}
	
	void Core::Update(float dt) {
		//for (unsigned ínt i = 0; i < this->m_systems.size(); ++i)
		//	this->m_systems[i].Update(dt, ObjectFactory->GetObjectList());
	}

	void Core::MainLoop(void) {
		while (42) {
			this->Update(0);
		}
	}

	void Core::Add(GameSystems::System *sys) {
		this->m_systems.push_back(sys);
	}
}