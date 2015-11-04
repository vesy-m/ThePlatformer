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

	enum objectType {
		NONE,
		PLAYER,
		PROJECTILE
	};

	class BaseGameObject
	{
	public:
		BaseGameObject();
		~BaseGameObject();
		std::vector<GameComponents::BaseComponent*> getComponents(GameComponents::COMPONENT_TYPE type);
		void attachComponent(GameComponents::BaseComponent*);
		void sendMessage(Message*);
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
		void setScale(float scale);
		float getScale();
		void setRotate(int rotate);
		int getRotate();
		void setName(std::string name);
		std::string getName();
		void setType(objectType newtype);
		objectType getType();

		void destroy(bool);
		bool destroy(void);
	private:
		std::vector<GameComponents::BaseComponent*> componentsList;
		int x;
		int y;
		int height;
		int width;
		int depth;
		float scale;
		int rotate;
		std::string name;
		objectType type;
		bool to_destroy;
	};
}


#endif // !_BASEGAMEOBJECT_H_