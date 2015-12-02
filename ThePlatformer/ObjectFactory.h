#pragma once
#ifndef _OBJECTFACTORY_H_
#define _OBJECTFACTORY_H_

#include <vector>
#include <list>
#include "BaseGameObject.h"
#include "gason.h"
#include "GameEngine.h"
#include "SpriteComponent.h"
#include "Menu.h"
#include "GraphicsSystem.h"

namespace GameComponents {
	class SpriteComponent;
}

namespace GameSystems {
	class ObjectFactory
	{
	public:
		enum gameState
		{
			MENU,
			LEVEL,
			NONE
		};
		enum ProjectileType {
			ARROW,
			SOCCER_BALL,
			TENNIS_BALL,
			BASE_BALL
		};
		static ObjectFactory& getInstance()
		{
			static ObjectFactory    instance;
			return instance;
		}
		~ObjectFactory();
		GameObjects::BaseGameObject *parseObject(GameTools::JsonValue&);
		GameObjects::BaseGameObject *createProjectile(GameObjects::BaseGameObject*, unsigned int, unsigned int, float, glm::vec2, ProjectileType);
		static void attachObject(GameObjects::BaseGameObject*);
		void buildLevel(GameTools::JsonValue&);
		GameEngine::Core::Level &getCurrentLevel();
		void buildMenu(GameTools::JsonValue & value);
		void LoadLevelFileAsCurrent(const std::string&);
		void LoadMenuFileAsCurrent(const std::string&);
		void cleanupObjects(void);
		std::list<GameObjects::BaseGameObject*>& getCurrentObjects();
		const std::list<GameSystems::BaseSystem *>& getSystems();
		void initSystems();
		void addSystems(GameSystems::BaseSystem*);
		gameState stateGame;
		std::string currentLevelFileName;
		//create for button and controller management
		bool controllerAlreadyTook(int idController);
		void removeAllPlayersWithController();
		void addOrChangePlayerWithController(int idController, int idPerso);
		void changeGameObjectSpriteComponent(GameObjects::BaseGameObject * obj, std::string filename);
		void playersReady(int nb);
		void changeSelectedButtonMenu(int idButton);
		void changeSelectedButtonMenu(GameObjects::BaseGameObject * button);
		void clearPlayers();
		void returnPrevMenuOrResumeLevel();
		void winTheGame(std::string);
		void checkWinCondition();
		GameObjects::BaseGameObject *isPLayersAlive();
		//----
	private:
		ObjectFactory();
		ObjectFactory(ObjectFactory const&) = delete;
		void operator=(ObjectFactory const&) = delete;
		void putObjectDepthOrdered(GameObjects::BaseGameObject*);
		std::list<GameObjects::BaseGameObject*> old_objects;
		std::list<GameSystems::BaseSystem*>		m_systems;

		std::vector<GameEngine::Core::Level> listLevels;
		GameEngine::Core::Level currentLevel;
		Menu currentMenu;
		bool systemNeedReinit;
		std::vector<GameObjects::BaseGameObject*> listPlayers;
		int nbPlayerReady;
		int countObjects;
		std::map<int, std::string> mapPlayersController;

	};
}

#endif // !_OBJECTFACTORY_H_