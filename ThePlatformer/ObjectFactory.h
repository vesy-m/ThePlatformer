#pragma once
#ifndef _OBJECTFACTORY_H_
#define _OBJECTFACTORY_H_

#include <vector>
#include "BaseGameObject.h"

namespace GameSystems {
	class ObjectFactory
	{
	public:
		ObjectFactory();
		~ObjectFactory();


	private:
		std::vector<GameObjects::BaseGameObject> listGameObject;
	};
}

#endif // !_OBJECTFACTORY_H_