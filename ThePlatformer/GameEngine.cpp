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
		for (auto it = this->m_systems.begin(); it != this->m_systems.end(); ++it)
			delete *it;
	}
	
	void Core::LoadLevelFile(const std::string &filename) {
		GameSystems::JSONParser fileParser(filename);
		GameSystems::ObjectFactory::getInstance().buildLevel(fileParser.getJSONValue());
	}

	void Core::Init(void) {
		this->m_manager = new TimeManager("../log_file.txt");
		for each (GameSystems::BaseSystem* system in this->m_systems)
			system->Init(GameSystems::ObjectFactory::getInstance().getCurrentLevel().getObjects());
	}

	void Core::Update(float dt) {
		//for (unsigned ínt i = 0; i < this->m_systems.size(); ++i)
		//	this->m_systems[i].Update(dt, ObjectFactory->GetObjectList());
	}

	void Core::MainLoop(void) {
		
		while (42) {
			this->m_manager->StartTimer();
			for each (GameSystems::BaseSystem *system in this->m_systems) {
				if (system->Update(this->m_manager->GetLastTime(), GameSystems::ObjectFactory::getInstance().getCurrentLevel().getObjects()) == 1) {
					return;
				}
			}
			GameSystems::ObjectFactory::getInstance().cleanupObjects();
			this->m_manager->WaitFPS(FRAME_PER_SECOND);
		}
	}

	void Core::Add(GameSystems::BaseSystem *sys) {
		this->m_systems.push_back(sys);
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
		std::vector<GameObjects::BaseGameObject *> playersList = std::vector<GameObjects::BaseGameObject *>();
		for (std::list<GameObjects::BaseGameObject *>::iterator it = this->listGameObject.begin(); it != this->listGameObject.end(); ++it) {
			if ((*it)->getType() == GameObjects::objectType::PLAYER) {
				playersList.push_back((*it));
			}
		}
		return playersList;
	}
}