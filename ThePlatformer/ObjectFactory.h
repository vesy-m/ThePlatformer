#pragma once
#ifndef _OBJECTFACTORY_H_
#define _OBJECTFACTORY_H_

#include <vector>
#include <list>
#include "BaseGameObject.h"

namespace GameSystems {
	class ObjectFactory
	{
	public:
		ObjectFactory();
		~ObjectFactory();
		static GameObjects::BaseGameObject *parseObject(JsonValue&);
		static void buildLevel(JsonValue&, std::list<GameObjects::BaseGameObject*>&);

	private:
		std::vector<GameObjects::BaseGameObject> listGameObject;
	};
}

#endif // !_OBJECTFACTORY_H_