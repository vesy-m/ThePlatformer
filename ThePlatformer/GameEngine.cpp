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
		/*for (auto it = listSystems.begin(); it != listSystems.end(); ++it)
			delete *it;*/
	}

	void Core::Init(void) {
		this->m_manager = new TimeManager("../log_file.txt");
	}

	void Core::Update(float dt) {
		//for (unsigned ínt i = 0; i < this->m_systems.size(); ++i)
		//	this->m_systems[i].Update(dt, ObjectFactory->GetObjectList());
	}

	void Core::MainLoop(void) {
		
		while (42) {
			this->m_manager->StartTimer();
			std::list<GameSystems::System *> listSystems = GameSystems::ObjectFactory::getInstance().getSystems();
			for each (GameSystems::System *system in listSystems) {
				if (system->Update(this->m_manager->GetLastTime(), GameSystems::ObjectFactory::getInstance().getCurrentObjects()) == 1) {
					return;
				}
			}
			GameSystems::ObjectFactory::getInstance().cleanupObjects();
			this->m_manager->WaitFPS(FRAME_PER_SECOND);
		}
	}

	void Core::Add(GameSystems::System *sys) {
		GameSystems::ObjectFactory::getInstance().addSystems(sys);
	}
}