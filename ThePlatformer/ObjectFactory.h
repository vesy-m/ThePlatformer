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
		void buildLevel(JsonValue&);
		std::list<GameObjects::BaseGameObject *> &getObjects();
	private:
		ObjectFactory();
		ObjectFactory(ObjectFactory const&) = delete;
		void operator=(ObjectFactory const&) = delete;

		void putObjectDepthOrdered(GameObjects::BaseGameObject * obj);
		std::list<GameObjects::BaseGameObject *> listGameObject;
		std::vector<Level> listLevels;
	};
}

#endif // !_OBJECTFACTORY_H_