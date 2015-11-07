#pragma once
#ifndef _OBJECTFACTORY_H_
#define _OBJECTFACTORY_H_

#include <vector>
#include <list>
#include "BaseGameObject.h"
#include "gason.h"
#include "Level.h"

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

		GameObjects::BaseGameObject *parseObject(JsonValue&);
		GameObjects::BaseGameObject *createArrow(unsigned int, unsigned int, float);
		static void attachObject(GameObjects::BaseGameObject*);
		void buildLevel(JsonValue&);
		Level &getCurrentLevel();
		void cleanupObjects(void);
	private:
		ObjectFactory();
		ObjectFactory(ObjectFactory const&) = delete;
		void operator=(ObjectFactory const&) = delete;

		void putObjectDepthOrdered(GameObjects::BaseGameObject*);
		
		std::list<GameObjects::BaseGameObject *> old_objects;


		std::vector<Level> listLevels;
		Level currentLevel;
	};
}

#endif // !_OBJECTFACTORY_H_