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
	class InputComponent;
	class SpriteComponent;
	class TextComponent;
	class VectorDebugComponent;
	class Collider;
	class BodyComponent;
	class ButtonComponent;
	class FireComponent;
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
		GameComponents::BaseComponent* getComponent(GameComponents::COMPONENT_TYPE);
		void Init(void);
		void attachComponent(GameComponents::InputComponent*);
		void attachComponent(GameComponents::SpriteComponent*);
		void attachComponent(GameComponents::TextComponent*);
		void attachComponent(GameComponents::VectorDebugComponent*);
		void attachComponent(GameComponents::Collider*);
		void attachComponent(GameComponents::BodyComponent*);
		void attachComponent(GameComponents::ButtonComponent*);
		void attachComponent(GameComponents::FireComponent*);
		void sendMessage(GameMessage::Message*);
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
		void setMass(float mass);
		float getMass();
		void setBounce(float bounce);
		float getBounce();
		void setRotate(int rotate);
		int getRotate();
		void setProjectileType(std::string);
		std::string getProjectileType();
		void setName(std::string name);
		std::string getName();
		void setType(objectType newtype);
		objectType getType();

		void destroy(bool);
		bool destroy(void);
	private:
		//std::vector<GameComponents::BaseComponent*> componentsList;
		GameComponents::InputComponent *m_input;
		GameComponents::SpriteComponent *m_sprite;
		GameComponents::TextComponent *m_text;
		GameComponents::VectorDebugComponent *m_vector;
		GameComponents::Collider *m_collider;
		GameComponents::BodyComponent *m_body;
		GameComponents::ButtonComponent *m_button;
		GameComponents::FireComponent *m_fire;
		int x;
		int y;
		int height;
		int width;
		int depth;
		int rotate;
		float scale;
		float mass;
		float bounce;
		std::string projectileType;
		std::string name;
		objectType type;
		bool to_destroy;
	};
}


#endif // !_BASEGAMEOBJECT_H_