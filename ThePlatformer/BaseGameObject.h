#pragma once
#ifndef _BASEGAMEOBJECT_H_
#define _BASEGAMEOBJECT_H_

#include <vector>
#include "BaseComponent.h"
#include <algorithm>
namespace GameComponents {
	enum COMPONENT_TYPE;
	class BaseComponent;
}

namespace GameObjects {

	class BaseGameObject
	{
	public:
		BaseGameObject();
		~BaseGameObject();
		std::vector<GameComponents::BaseComponent*> getComponents(GameComponents::COMPONENT_TYPE type);
		void attachComponent(GameComponents::BaseComponent*);
	private:
		std::vector<GameComponents::BaseComponent*> componentsList;
	};
}


#endif // !_BASEGAMEOBJECT_H_