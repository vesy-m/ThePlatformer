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
		//long long loopAverTime = 0;
		//long long list[4];
		int i = 0;
		int nbLoop = 0;
		while (Core::gameLoop) {
			//auto oneLoop = std::chrono::high_resolution_clock::now();
			std::list<GameSystems::BaseSystem *> listSystems = GameSystems::ObjectFactory::getInstance().getSystems();
			std::list<GameObjects::BaseGameObject * > listCurrentObjects = GameSystems::ObjectFactory::getInstance().getCurrentObjects();
			this->m_manager->StartTimer();
			i = 0;
			for each (GameSystems::BaseSystem *system in listSystems) {
				//auto sysDuration = std::chrono::high_resolution_clock::now(); 
				if (system->Update(this->m_manager->GetLastTime(), listCurrentObjects) == 1) return;
				//list[i] = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - sysDuration).count();
				i++;
			}
			GameSystems::ObjectFactory::getInstance().checkWinCondition();
			GameSystems::ObjectFactory::getInstance().cleanupObjects();
			//loopAverTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - oneLoop).count();
			this->m_manager->WaitFPS(FRAME_PER_SECOND);
			//if (nbLoop >= 60) {
			/*if (loopAverTime > 20000) {
				std::cout << "---------------------------------------------------" << std::endl;
				//std::cout << "Loop Time : " << std::setw(13) << loopAverTime / nbLoop << std::endl;
				std::cout << "Loop Time : " << std::setw(13) << loopAverTime << std::endl;
				loopAverTime = 0;
				long long add = 0;
				for (i = 0; i < 4; i++)
				{
					//std::cout << "system : " << std::setw(16) << list[i] / nbLoop << std::endl;
					//add += list[i] / nbLoop;
					std::cout << "system : " << std::setw(16) << list[i] << std::endl;
					add += list[i];
					list[i] = 0;
				}
				std::cout << "Addition Sys : " << std::setw(10) << add << std::endl;
				std::cout << "Sprite :       " << std::setw(10) << GameTools::debugManager::getInstance().time1 << std::endl;
				std::cout << "debug  :       " << std::setw(10) << GameTools::debugManager::getInstance().time2 << std::endl;
				std::cout << "text   :       " << std::setw(10) << GameTools::debugManager::getInstance().time3 << std::endl;
				std::cout << "time 1 :       " << std::setw(10) << GameTools::debugManager::getInstance().time4 << std::endl;
				nbLoop = -1;
			}
			nbLoop++;*/
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