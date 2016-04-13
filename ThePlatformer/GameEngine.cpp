#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "GameEngine.h"
#include "BaseSystem.h"
#include "JSONParser.h"
#include "ObjectFactory.h"

namespace GameEngine {

	bool Core::gameLoop = true;

	Core::Core() {
	}

	Core::~Core() {
		delete this->m_manager;
	}
	
	void Core::Init(void) {
		this->m_manager = new TimeManager();
	}

	void Core::Update(float dt) {
	}

	void Core::MainLoop(void) {
		//clock_t oneLoop;
		//clock_t saveBefore;
		//clock_t saveAfter;
		//clock_t tick;
		//float list[4];
		int i = 0;
		while (Core::gameLoop) {
			//oneLoop = clock();
			std::list<GameSystems::BaseSystem *> listSystems = GameSystems::ObjectFactory::getInstance().getSystems();
			std::list<GameObjects::BaseGameObject * > listCurrentObjects = GameSystems::ObjectFactory::getInstance().getCurrentObjects();
			this->m_manager->StartTimer();
			i = 0;
			for each (GameSystems::BaseSystem *system in listSystems) {
				//tick = clock();
				if (system->Update(this->m_manager->GetLastTime(), listCurrentObjects) == 1) return;
				//tick = clock() - tick;
				//list[i] = ((float)tick) / CLOCKS_PER_SEC;
				i++;
			}
			GameSystems::ObjectFactory::getInstance().checkWinCondition();
			GameSystems::ObjectFactory::getInstance().cleanupObjects();
			//saveBefore = clock() - oneLoop;
			this->m_manager->WaitFPS(FRAME_PER_SECOND);
			//saveAfter = clock() - oneLoop;
			//if (saveBefore >= saveAfter) {
			//	std::cout << "---------------------------------------------------" << std::endl;
			//	std::cout << "Before Wait : " << ((float)saveBefore) / CLOCKS_PER_SEC << std::endl;
			//	std::cout << "After Wait : " << ((float)saveAfter) / CLOCKS_PER_SEC << std::endl;
			//	for (i = 0; i < 4; i++)
			//	{
			//		std::cout << "system : " << list[i] << std::endl;
			//	}
			//}
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
			if ((*it)->getType() == GameObjects::objectType::PLAYER || (*it)->getType() == GameObjects::objectType::PLAYER_ATTACK) playersList.push_back((*it));
		return playersList;
	}
}