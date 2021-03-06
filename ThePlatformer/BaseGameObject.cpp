#include "BaseGameObject.h"
#include "BodyComponent.h"
#include "Collider.h"
#include "InputComponent.h"
#include "SpriteComponent.h"
#include "AimComponent.h"
#include "TextComponent.h"
#include "VectorDebugComponent.h"
#include "ButtonComponent.h"
#include "FireComponent.h"
#include "FireMessage.h"
#include "AudioComponent.h"
#include "CAAttackComponent.h"
#include "TimerComponent.h"
#include "EditorElementSelectorComponent.h"
#include "EditorCaseSelectorComponent.h"
#include "EditorKeyboardInputComponent.h"
#include "LifeBarComponent.h"
#include "AutoPlayComponent.h"
#include "InGameBannerComponent.h"

namespace GameObjects {
	BaseGameObject::BaseGameObject()
	{
		x = 0;
		y = 0;
		height = 0;
		width = 0;
		depth = 0;
		rotate = 0;
		scale = 1;
		mass = 1.0f;
		moveSpeed = 1.0f;
		bounce = 0.0f;
		name = "";
		to_destroy = false;
		invicible = false;
		life = 200;
		type = objectType::NONE;
		this->m_body = NULL;
		this->m_collider = NULL;
		this->m_input = NULL;
		this->m_sprite = NULL;
		this->m_text = NULL;
		this->m_vector = NULL;
		this->m_aim = NULL;
		this->m_sound = NULL;
		this->m_attack = NULL;
		this->m_timer = NULL;
		this->m_editorSelector = NULL;
		this->m_caseSelector = NULL;
		this->m_editorKeyboard = NULL;
		this->m_lifeBarComponent = NULL;
		this->m_autoPlayComponent = NULL;
		this->m_inGameBannerComponent = NULL;
		this->attack_1_value = 0;
		this->attack_2_value = 0;
		this->attack_3_value = 0;
		this->jump_value = 200;
		this->powerupDamage = 1;
		this->powerupDefense = 1;
	}

	void BaseGameObject::Init(void) {
		if (this->m_body) this->m_body->Init();
		if (this->m_collider) this->m_collider->Init();
		if (this->m_input) this->m_input->Init();
		if (this->m_sprite) this->m_sprite->Init();
		if (this->m_text) this->m_text->Init();
		if (this->m_vector) this->m_vector->Init();
		if (this->m_fire) this->m_fire->Init();
		if (this->m_aim) this->m_aim->Init();
		if (this->m_sound) this->m_sound->Init();
		if (this->m_attack) this->m_attack->Init();
		if (this->m_timer) this->m_timer->Init();
		if (this->m_editorSelector) this->m_editorSelector->Init();
		if (this->m_caseSelector) this->m_caseSelector->Init();
		if (this->m_editorKeyboard) this->m_editorKeyboard->Init();
	}

	BaseGameObject::~BaseGameObject()
	{
		delete this->m_body;
		delete this->m_collider;
		delete this->m_input;
		delete this->m_sprite;
		delete this->m_text;
		delete this->m_vector;
		delete this->m_aim;
		delete this->m_sound;
		delete this->m_attack;
		delete this->m_timer;
		delete this->m_editorSelector;
		delete this->m_caseSelector;
		delete this->m_editorKeyboard;
		delete this->m_lifeBarComponent;
		delete this->m_autoPlayComponent;
		delete this->m_inGameBannerComponent;
	}

	GameComponents::BaseComponent *BaseGameObject::getComponent(GameComponents::COMPONENT_TYPE type) {
		switch (type) {
		case GameComponents::CIRCLE_COLLIDER:
		case GameComponents::BOX_COLLIDER:
		case GameComponents::COLLIDER:
			return this->m_collider;
		case GameComponents::DEBUGVECTOR:
			return this->m_vector;
		case GameComponents::PHYSIC:
			return this->m_body;
		case GameComponents::WINDOW:
			return this->m_input;
		case GameComponents::TEXT:
			return this->m_text;
		case GameComponents::SPRITE:
			return this->m_sprite;
		case GameComponents::BUTTON:
			return this->m_button;
		case GameComponents::AIM:
			return this->m_aim;
		case GameComponents::SOUND:
			return this->m_sound;
		case GameComponents::ATTACK:
			return this->m_attack;
		case GameComponents::MECHANIC:
			return this->m_timer;
		case GameComponents::ELEMENT_SELECTOR:
			return this->m_editorSelector;
		case GameComponents::CASE_SELECTOR:
			return this->m_caseSelector;
		case GameComponents::EDITOR_KEYBOARD:
			return this->m_editorKeyboard;
		case GameComponents::LIFE_BAR:
			return this->m_lifeBarComponent;
		case GameComponents::AUTO_PLAY:
			return this->m_autoPlayComponent;
		case GameComponents::BANNER:
			return this->m_inGameBannerComponent;
		default:
			return NULL;
		}
	}

	void BaseGameObject::attachComponent(GameComponents::InputComponent *input)
	{
		this->m_input = input;
	}

	void BaseGameObject::attachComponent(GameComponents::ColliderComponent *collider)
	{
		this->m_collider = collider;
	}

	void BaseGameObject::attachComponent(GameComponents::VectorDebugComponent *vector)
	{
		this->m_vector = vector;
	}

	void BaseGameObject::attachComponent(GameComponents::TextComponent *text)
	{
		this->m_text = text;
	}

	void BaseGameObject::attachComponent(GameComponents::SpriteComponent *sprite)
	{
		this->m_sprite = sprite;
	}

	void BaseGameObject::attachComponent(GameComponents::BodyComponent *body)
	{
		this->m_body = body;
	}

	void BaseGameObject::attachComponent(GameComponents::ButtonComponent *button)
	{
		this->m_button = button;
	}

	void BaseGameObject::attachComponent(GameComponents::FireComponent *fire)
	{
		this->m_fire = fire;
	}

	void BaseGameObject::attachComponent(GameComponents::CAAttackComponent *attack)
	{
		this->m_attack = attack;
	}

	void BaseGameObject::attachComponent(GameComponents::AimComponent *aim)
	{
		this->m_aim = aim;
	}

	void BaseGameObject::attachComponent(GameComponents::AudioComponent *sound)
	{
		this->m_sound = sound;
	}

	void BaseGameObject::attachComponent(GameComponents::TimerComponent *deathTimer)
	{
		this->m_timer = deathTimer;
	}

	void BaseGameObject::attachComponent(GameComponents::EditorElementSelectorComponent *editorSelector)
	{
		this->m_editorSelector = editorSelector;
	}

	void BaseGameObject::attachComponent(GameComponents::EditorCaseSelectorComponent *caseSelector)
	{
		this->m_caseSelector = caseSelector;
	}

	void BaseGameObject::attachComponent(GameComponents::EditorKeyboardInputComponent *editorKeyboard)
	{
		this->m_editorKeyboard = editorKeyboard;
	}

	void BaseGameObject::attachComponent(GameComponents::LifeBarComponent *lifeBarComponent)
	{
		this->m_lifeBarComponent = lifeBarComponent;
	}

	void BaseGameObject::attachComponent(GameComponents::AutoPlayComponent *autoPlayComponent)
	{
		this->m_autoPlayComponent = autoPlayComponent;
	}

	void BaseGameObject::attachComponent(GameComponents::InGameBannerComponent *inGameBannerComponent)
	{
		this->m_inGameBannerComponent = inGameBannerComponent;
	}

	void BaseGameObject::sendMessage(GameMessage::Message *message)
	{
		if (this->m_body) this->m_body->sendMessage(message);
		if (this->m_collider) this->m_collider->sendMessage(message);
		if (this->m_input) this->m_input->sendMessage(message);
		if (this->m_sprite) this->m_sprite->sendMessage(message);
		if (this->m_text) this->m_text->sendMessage(message);
		if (this->m_vector) this->m_vector->sendMessage(message);
		if (this->m_button) this->m_button->sendMessage(message);
		if (this->m_aim) this->m_aim->sendMessage(message);
		if (this->m_attack) this->m_attack->sendMessage(message);
		if (message->id == GameMessage::DAMAGE) this->setDamage(dynamic_cast<GameMessage::DamageMessage*>(message));
		if (this->m_sound) this->m_sound->sendMessage(message);
		if (this->m_editorSelector) this->m_editorSelector->sendMessage(message);
		if (this->m_caseSelector) this->m_caseSelector->sendMessage(message);
		if (this->m_editorKeyboard) this->m_editorKeyboard->sendMessage(message);
		if (this->m_lifeBarComponent) this->m_lifeBarComponent->sendMessage(message);
		if (this->m_autoPlayComponent) this->m_autoPlayComponent->sendMessage(message);
		if (this->m_inGameBannerComponent) this->m_inGameBannerComponent->sendMessage(message);
		delete message;
	}

	void BaseGameObject::setX(int x)
	{
		this->x = x;

	}
	int BaseGameObject::getX()
	{
		return this->x;
	}
	void BaseGameObject::setY(int y)
	{
		this->y = y;
	}
	int BaseGameObject::getY()
	{
		return this->y;
	}
	int BaseGameObject::getHeight()
	{
		return this->height;
	}

	int BaseGameObject::getWidth()
	{
		return this->width;
	}
	void BaseGameObject::setDepth(int depth)
	{
		this->depth = depth;
	}
	int BaseGameObject::getDepth()
	{
		return this->depth;
	}
	void BaseGameObject::setHeight(int height)
	{
		this->height = (int)(height * scale);
	}
	void BaseGameObject::setWidth(int width)
	{
		this->width = (int)(width * scale);
	}
	void BaseGameObject::setScale(float scale)
	{
		this->scale = scale;
	}
	float BaseGameObject::getScale()
	{
		return this->scale;
	}
	void BaseGameObject::setMass(float mass)
	{
		this->mass = mass;
	}
	float BaseGameObject::getMass()
	{
		return this->mass;
	}
	void BaseGameObject::setMoveSpeed(float moveSpeed)
	{
		this->moveSpeed = moveSpeed;
	}
	float BaseGameObject::getMoveSpeed()
	{
		return this->moveSpeed;
	}
	void BaseGameObject::setBounce(float bounce)
	{
		this->bounce = bounce;
	}
	float BaseGameObject::getBounce()
	{
		return this->bounce;
	}
	void BaseGameObject::setRotate(int rotate)
	{
		this->rotate = rotate;
	}
	int BaseGameObject::getRotate()
	{
		return this->rotate;
	}
	void BaseGameObject::setProjectileType(ProjectileType projectileType)
	{
		this->projectileType = projectileType;
	}
	ProjectileType BaseGameObject::getProjectileType()
	{
		return this->projectileType;
	}
	void BaseGameObject::setName(std::string name)
	{
		this->name = name;
	}
	std::string BaseGameObject::getName()
	{
		return name;
	}
	void BaseGameObject::setType(objectType newtype)
	{
		this->type = newtype;
	}
	objectType BaseGameObject::getType()
	{
		return this->type;
	}

	int BaseGameObject::getLife()
	{
		return this->life;
	}

	void BaseGameObject::setDamage(GameMessage::DamageMessage *damageMsg)
	{
		if (invicible)
			return;

		this->life -= (int) std::round((float)damageMsg->damage * this->powerupDefense);

		if (damageMsg->damageType == GameMessage::DamageMessage::DASH) {
			GameComponents::TimerComponent* timer = new GameComponents::TimerComponent(this);
			timer->Init();
			timer->setTimerType(GameObjects::DASH_DAMAGE);
			timer->setTime(350);
			this->setInvicible(true);
			timer->startTimer();
		}

		if (this->life <= 0)
			GameSystems::ObjectFactory::getInstance().killPlayerByObject(this);
	}

	int BaseGameObject::getPower()
	{
		return this->power;
	}

	void BaseGameObject::setPower(int power)
	{
		this->power = power;
	}

	void BaseGameObject::setInvicible(bool inv)
	{
		this->invicible = inv;
	}

	bool BaseGameObject::getInvicible(void) const
	{
		return invicible;
	}

	void BaseGameObject::destroy(bool des) {
		to_destroy = des;
	}

	bool BaseGameObject::destroy(void) {
		return to_destroy;
	}

	float BaseGameObject::getAttack1Value(void) {
		return (this->attack_1_value);
	}

	float BaseGameObject::getAttack2Value(void) {
		return (this->attack_2_value);
	}

	float BaseGameObject::getAttack3Value(void) {
		return (this->attack_3_value);
	}

	float BaseGameObject::getJumpValue(void) {
		return (this->jump_value);
	}

	int BaseGameObject::getPowerupDamage(void)
	{
		return this->powerupDamage;
	}

	int BaseGameObject::getPowerupDefense(void)
	{
		return this->powerupDefense;
	}

	void BaseGameObject::setPowerupDamage(int mult)
	{
		if (mult == 0)
			mult = 1;
		this->powerupDamage = mult;
	}

	void BaseGameObject::setPowerupDefense(int mult)
	{
		if (mult == 0)
			mult = 1;
		this->powerupDefense = mult;
	}

	void BaseGameObject::setAttack1Value(float attack_1_value) {
		this->attack_1_value = attack_1_value;
	}

	void BaseGameObject::setAttack2Value(float attack_2_value) {
		this->attack_2_value = attack_2_value;
	}

	void BaseGameObject::setAttack3Value(float attack_3_value) {
		this->attack_3_value = attack_3_value;
	}
}
