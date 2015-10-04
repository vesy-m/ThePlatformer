#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "GameEngine.h"
#include "System.h"
#include "JSONParser.h"
#include "ObjectFactory.h"

namespace GameEngine {
	Core::Core() {
	}

	Core::~Core() {
		delete this->m_manager;
		for (auto it = this->m_systems.begin(); it != this->m_systems.end(); ++it)
			delete *it;
	}
	
	void Core::LoadLevelFile(const std::string &filename) {
		GameSystems::JSONParser fileParser(filename);
		GameSystems::ObjectFactory::buildLevel(fileParser.getJSONValue(), this->m_objects);
	}

	void Core::Init(void) {
		this->m_manager = new TimeManager("../log_file.txt");
		for each (GameSystems::System* system in this->m_systems)
			system->Init(this->m_objects);
	}

	void Core::Update(float dt) {
		//for (unsigned �nt i = 0; i < this->m_systems.size(); ++i)
		//	this->m_systems[i].Update(dt, ObjectFactory->GetObjectList());
	}

	void Core::MainLoop(void) {
		
		while (42) {
			this->m_manager->StartTimer();
			for each (GameSystems::System *system in this->m_systems) {
				if (system->Update(this->m_manager->GetLastTime(), this->m_objects) == 1) {
					return;
				}
			}
			this->m_manager->WaitFPS(FRAME_PER_SECOND);
		}
	}

	void Core::Add(GameObjects::BaseGameObject *object) {
		this->m_objects.push_back(object);
	}

	void Core::Add(GameSystems::System *sys) {
		this->m_systems.push_back(sys);
	}
}