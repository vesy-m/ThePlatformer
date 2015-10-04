#pragma once
#ifndef _BASEGAMEOBJECT_H_
#define _BASEGAMEOBJECT_H_

#include <vector>
#include "BaseComponent.h"
#include "Message.h"
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
		void SendMessage(Message*);
		void setX(int x);
		int getX();
		void setY(int y);
		int getY();
		int getHeight();
		int getWidth();
		void setDepth(int depth);
		int getDepth();
		void setHeight(int height);
		void setWidth(int width);
	private:
		std::vector<GameComponents::BaseComponent*> componentsList;
		int x;
		int y;
		int height;
		int width;
		int depth;
	};
}


#endif // !_BASEGAMEOBJECT_H_