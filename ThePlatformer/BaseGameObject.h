#pragma once
#include <vector>
#include "BaseComponent.h"
#include "Message.h"
#include "DamageMessage.h"
#include <algorithm>

namespace GameComponents {
	enum COMPONENT_TYPE;
	class BaseComponent;
	class InputComponent;
	class SpriteComponent;
	class AimComponent;
	class TextComponent;
	class VectorDebugComponent;
	class ColliderComponent;
	class BodyComponent;
	class ButtonComponent;
	class FireComponent;
	class CAAttackComponent;
	class AudioComponent;
	class DeathTimerComponent;
}

namespace GameObjects {

	enum objectType {
		NONE,
		PLAYER,
		PROJECTILE
	};

	enum ProjectileType {
		ARROW,
		SOCCER_BALL,
		TENNIS_BALL,
		BASE_BALL,
		BAT,
		BLOCK
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
		void attachComponent(GameComponents::ColliderComponent*);
		void attachComponent(GameComponents::BodyComponent*);
		void attachComponent(GameComponents::ButtonComponent*);
		void attachComponent(GameComponents::FireComponent*);
		void attachComponent(GameComponents::CAAttackComponent*);
		void attachComponent(GameComponents::AimComponent*);
		void attachComponent(GameComponents::AudioComponent*);
		void attachComponent(GameComponents::DeathTimerComponent*);
		void sendMessage(GameMessage::Message*);
		void setX(int x);
		int getX();
		void setY(int y);
		int getY();
		int getHeight();
		int getWidth();
		void setDepth(int);
		int getDepth();
		void setHeight(int);
		void setWidth(int);
		void setScale(float);
		float getScale();
		void setMass(float);
		float getMass();
		void setBounce(float);
		float getBounce();
		void setRotate(int);
		int getRotate();
		void setProjectileType(ProjectileType);
		ProjectileType getProjectileType();
		void setName(std::string);
		std::string getName();
		void setType(objectType);
		objectType getType();
		int getLife();
		void setDamage(GameMessage::DamageMessage*);
		int getPower();
		void setPower(int);
		float getCooldown();
		void setCooldown(float);

		void setInvicible(void);
		bool getInvicible(void);

		void destroy(bool);
		bool destroy(void);
	private:
		GameComponents::InputComponent *m_input;
		GameComponents::SpriteComponent *m_sprite;
		GameComponents::TextComponent *m_text;
		GameComponents::VectorDebugComponent *m_vector;
		GameComponents::ColliderComponent *m_collider;
		GameComponents::BodyComponent *m_body;
		GameComponents::ButtonComponent *m_button;
		GameComponents::FireComponent *m_fire;
		GameComponents::AimComponent *m_aim;
		GameComponents::AudioComponent *m_sound;
		GameComponents::CAAttackComponent *m_attack;
		GameComponents::DeathTimerComponent *m_deathTimer;
		int x;
		int y;
		int height;
		int width;
		int depth;
		int rotate;
		float scale;
		float mass;
		float bounce;
		ProjectileType projectileType;
		std::string name;
		objectType type;
		bool to_destroy;
		bool invicible;
		int life = 100;
		int power = 0;
		float cooldown = 2000.0f;
	};
}