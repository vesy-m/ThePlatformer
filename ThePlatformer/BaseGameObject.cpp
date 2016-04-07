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
#include "EditorElementSelectorComponent.h"
#include "EditorCaseSelectorComponent.h"
#include "EditorKeyboardInputComponent.h"

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
		bounce = 0.0f;
		to_destroy = false;
		invicible = false;
		type = objectType::NONE;
		this->m_body = NULL;
		this->m_collider = NULL;
		this->m_input = NULL;
		this->m_sprite = NULL;
		this->m_text = NULL;
		this->m_vector = NULL;
		this->m_aim = NULL;
		this->m_sound = NULL;
		this->m_editorSelector = NULL;
		this->m_caseSelector = NULL;
		this->m_editorKeyboard = NULL;
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
		delete this->m_editorSelector;
		delete this->m_caseSelector;
		delete this->m_editorKeyboard;
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
		case GameComponents::ELEMENT_SELECTOR:
			return this->m_editorSelector;
		case GameComponents::CASE_SELECTOR:
			return this->m_caseSelector;
		case GameComponents::EDITOR_KEYBOARD:
			return this->m_editorKeyboard;
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

	void BaseGameObject::attachComponent(GameComponents::AimComponent *aim)
	{
		this->m_aim = aim;
	}

	void BaseGameObject::attachComponent(GameComponents::AudioComponent *sound)
	{
		this->m_sound = sound;
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
		if (this->m_fire && message->id == GameMessage::FIRE) this->m_fire->sendMessage(message);
		if (message->id == GameMessage::DAMAGE) this->setDamage(dynamic_cast<GameMessage::DamageMessage*>(message));
		if (this->m_sound) this->m_sound->sendMessage(message);
		if (this->m_editorSelector) this->m_editorSelector->sendMessage(message);
		if (this->m_caseSelector) this->m_caseSelector->sendMessage(message);
		if (this->m_editorKeyboard) this->m_editorKeyboard->sendMessage(message);
	}

	void BaseGameObject::setX(int x)
	{
		/*
		if (x < 0) this->x = 1;
		else if (x + this->getWidth() >= 1280) this->x = 1280 - this->getWidth();
		else this->x = x;*/
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
	void BaseGameObject::setProjectileType(std::string projectileType)
	{
		this->projectileType = projectileType;
	}
	std::string BaseGameObject::getProjectileType()
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

		this->life -= damageMsg->damage;

		if (this->life <= 0)
			this->destroy(true);
	}

	int BaseGameObject::getPower()
	{
		return this->power;
	}

	void BaseGameObject::setPower(int power)
	{
		this->power = power;
	}

	float BaseGameObject::getCooldown()
	{
		return this->cooldown;
	}

	void BaseGameObject::setCooldown(float cooldown)
	{
		this->cooldown = cooldown;
	}

	void BaseGameObject::setInvicible(void)
	{
		this->invicible = !invicible;
	}

	bool BaseGameObject::getInvicible(void)
	{
		return invicible;
	}

	void BaseGameObject::destroy(bool des) {
		to_destroy = des;
	}

	bool BaseGameObject::destroy(void) {
		return to_destroy;
	}
}
