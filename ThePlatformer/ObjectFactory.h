#pragma once
#ifndef _OBJECTFACTORY_H_
#define _OBJECTFACTORY_H_

#include <vector>
#include <list>
#include "BaseGameObject.h"
#include "Projectile.h"
#include "gason.h"
#include "GameEngine.h"
#include "SpriteComponent.h"

namespace GameComponents {
	class SpriteComponent;
}

namespace GameSystems {
	class ObjectFactory
	{
	public:
		static ObjectFactory& getInstance()
		{
			static ObjectFactory    instance;
			return instance;
		}
		~ObjectFactory();
		GameObjects::BaseGameObject *parseObject(GameTools::JsonValue&);
		GameObjects::BaseGameObject *createArrow(GameObjects::BaseGameObject*, unsigned int, unsigned int, float, glm::vec2);
		static void attachObject(GameObjects::BaseGameObject*);
		void buildLevel(GameTools::JsonValue&);
		GameEngine::Core::Level &getCurrentLevel();
		void cleanupObjects(void);
	private:
		ObjectFactory();
		ObjectFactory(ObjectFactory const&) = delete;
		void operator=(ObjectFactory const&) = delete;
		void putObjectDepthOrdered(GameObjects::BaseGameObject*);
		std::list<GameObjects::BaseGameObject *> old_objects;
		std::vector<GameEngine::Core::Level> listLevels;
		GameEngine::Core::Level currentLevel;
	};
}

#endif // !_OBJECTFACTORY_H_