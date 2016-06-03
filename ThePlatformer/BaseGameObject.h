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
	class TimerComponent;
	class EditorElementSelectorComponent;
	class EditorCaseSelectorComponent;
	class EditorKeyboardInputComponent;
	class LifeBarComponent;
	class AutoPlayComponent;
}

namespace GameObjects {

	enum objectType {
		NONE,
		PLAYER,
		PROJECTILE,
		PROJECTILE_BREAK,
		PLAYER_ATTACK,
		PLAYER_BLOCK

	};

	enum ProjectileType {
		ARROW,
		SOCCER_BALL,
		TENNIS_BALL1,
		TENNIS_BALL2,
		TENNIS_BREAK,
		BASE_BALL,
		BAT,
		BLOCK,
		DROP,
		RUGBY_BALL,
		DASH,
		DASH_DAMAGE,
		PUNCH,
		SPECIAL_PUNCH,
		BOXER_POWERUP,
		BOXER_POWERUP_AURA
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
		void attachComponent(GameComponents::TimerComponent*);
		void attachComponent(GameComponents::EditorElementSelectorComponent *);
		void attachComponent(GameComponents::EditorCaseSelectorComponent *);
		void attachComponent(GameComponents::EditorKeyboardInputComponent *);
		void attachComponent(GameComponents::LifeBarComponent *);
		void attachComponent(GameComponents::AutoPlayComponent *);
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
		void setMoveSpeed(float);
		float getMoveSpeed();
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

		void setInvicible(bool);
		bool getInvicible(void) const;

		void destroy(bool);
		bool destroy(void);

		float getAttack1Value(void);
		float getAttack2Value(void);
		float getAttack3Value(void);
		float getJumpValue(void);

		int getPowerupDamage(void);
		int getPowerupDefense(void);
		void setPowerupDamage(int);
		void setPowerupDefense(int);

		void setAttack1Value(float);
		void setAttack2Value(float);
		void setAttack3Value(float);
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
		GameComponents::TimerComponent *m_timer;
		GameComponents::EditorElementSelectorComponent *m_editorSelector;
		GameComponents::EditorCaseSelectorComponent *m_caseSelector;
		GameComponents::EditorKeyboardInputComponent *m_editorKeyboard;
		GameComponents::LifeBarComponent *m_lifeBarComponent;
		GameComponents::AutoPlayComponent *m_autoPlayComponent;
		int x;
		int y;
		int height;
		int width;
		int depth;
		int rotate;
		float scale;
		float mass;
		float moveSpeed;
		float bounce;
		ProjectileType projectileType;
		std::string name;
		objectType type;
		bool to_destroy;
		bool invicible;
		int life;
		int power = 0;

		int powerupDamage;
		int powerupDefense;

		float attack_1_value;
		float attack_2_value;
		float attack_3_value;
		float jump_value;
	};
}