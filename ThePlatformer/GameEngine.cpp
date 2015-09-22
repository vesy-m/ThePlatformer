#include <iostream>
#include "GameEngine.h"
#include "System.h"

namespace GameEngine {
	Core::Core() {
		this->m_systems = std::vector<System *>();
	}

	Core::~Core() {

	}
	
	void Core::Update(float dt) {
		//for (unsigned i = 0; i < this->m_systems.size(); ++i)
		//	this->m_systems[i].Update(dt, ObjectFactory->GetObjectList());
	}

	void Core::MainLoop(void) {
		while (42) {
			this->Update(0);
		}
	}

	void Core::Add(System *sys) {
		this->m_systems.push_back(sys);
	}
}