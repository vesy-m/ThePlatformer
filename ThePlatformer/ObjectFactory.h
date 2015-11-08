#pragma once
#ifndef _OBJECTFACTORY_H_
#define _OBJECTFACTORY_H_

#include <vector>
#include <list>
#include "BaseGameObject.h"
#include "gason.h"
#include "Level.h"
#include "SpriteComponent.h"
#include "Menu.h"

namespace GameComponents {
	class SpriteComponent;
}

namespace GameSystems {
	class ObjectFactory
	{
		enum gameState
		{
			MENU,
			LEVEL,
			NONE
		};

	public:
		static ObjectFactory& getInstance()
		{
			static ObjectFactory    instance;
			return instance;
		}
		~ObjectFactory();

		GameObjects::BaseGameObject *parseObject(JsonValue&);
		GameObjects::BaseGameObject *createArrow(unsigned int, unsigned int, float, bool);
		static void attachObject(GameObjects::BaseGameObject*);
		void buildLevel(JsonValue&);
		void buildMenu(JsonValue & value);
		void LoadLevelFileAsCurrent(const std::string & filename);
		void LoadMenuFileAsCurrent(const std::string & filename);
		Level &getCurrentLevel();
		void cleanupObjects(void);
		std::list<GameObjects::BaseGameObject*>& getCurrentObjects();
		const std::list<GameSystems::System *> &getSystems();
		void initSystems();
		void addSystems(GameSystems::System *);
	private:
		ObjectFactory();
		ObjectFactory(ObjectFactory const&) = delete;
		void operator=(ObjectFactory const&) = delete;

		void putObjectDepthOrdered(GameObjects::BaseGameObject*);
		
		std::list<GameObjects::BaseGameObject *> old_objects;
		std::list<GameSystems::System *>		m_systems;

		std::vector<Level> listLevels;
		Level currentLevel;
		Menu currentMenu;
		gameState stateGame;

	};
}

#endif // !_OBJECTFACTORY_H_