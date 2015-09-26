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
		void setX(int x);
		int getX();
		void setY(int y);
		int getY();
	private:
		std::vector<GameComponents::BaseComponent*> componentsList;
		int x = 400;
		int y = 0;
	};
}


#endif // !_BASEGAMEOBJECT_H_