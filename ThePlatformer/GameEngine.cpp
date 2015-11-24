#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "GameEngine.h"
#include "BaseSystem.h"
#include "JSONParser.h"
#include "ObjectFactory.h"

namespace GameEngine {
	Core::Core() {
	}

	Core::~Core() {
		delete this->m_manager;
	}
	
	void Core::Init(void) {
		this->m_manager = new TimeManager("../log_file.txt");
	}

	void Core::Update(float dt) {
	}

	void Core::MainLoop(void) {
		
		while (42) {
			std::list<GameSystems::BaseSystem *> listSystems = GameSystems::ObjectFactory::getInstance().getSystems();
			std::list<GameObjects::BaseGameObject * > listCurrentObjects = GameSystems::ObjectFactory::getInstance().getCurrentObjects();
			this->m_manager->StartTimer();
			for each (GameSystems::BaseSystem *system in listSystems)
				if (system->Update(this->m_manager->GetLastTime(), listCurrentObjects) == 1) return;
			GameSystems::ObjectFactory::getInstance().cleanupObjects();
			this->m_manager->WaitFPS(FRAME_PER_SECOND);
		}
	}

	void Core::Add(GameSystems::BaseSystem *sys) {
		GameSystems::ObjectFactory::getInstance().addSystems(sys);
	}

	Core::Level::Level()
	{
	}

	Core::Level::~Level()
	{
	}

	void Core::Level::putObjectDepthOrdered(GameObjects::BaseGameObject * obj) {
		int depth = obj->getDepth();
		int size = (int) this->listGameObject.size();

		for (std::list<GameObjects::BaseGameObject *>::iterator it = this->listGameObject.begin(); it != this->listGameObject.end(); ++it) {
			if ((*it)->getDepth() <= depth) {
				this->listGameObject.insert(it, obj);
				return;
			}
		}
		this->listGameObject.push_back(obj);
	}

	std::list<GameObjects::BaseGameObject *> &Core::Level::getObjects()
	{
		return this->listGameObject;
	}

	std::vector<GameObjects::BaseGameObject *> Core::Level::getPlayers()
	{
		std::vector<GameObjects::BaseGameObject *>playersList;
		for (std::list<GameObjects::BaseGameObject *>::iterator it = this->listGameObject.begin(); it != this->listGameObject.end(); ++it)
			if ((*it)->getType() == GameObjects::objectType::PLAYER) playersList.push_back((*it));
		return playersList;
	}
}