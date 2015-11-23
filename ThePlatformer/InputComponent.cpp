#include "InputComponent.h"

namespace GameComponents {

	InputComponent::InputComponent(GameObjects::BaseGameObject *object) : BaseComponent(object)
	{
		object->attachComponent(this);
		this->duration = 500.0f;
		this->savedDt = 0.0f;
		this->maxElapsedTime = 2000.0f;
	}

	InputComponent::~InputComponent()
	{
	}

	GameObjects::BaseGameObject * InputComponent::getComposition()
	{
		return this->composition;
	}

	void InputComponent::Update(double dt)
	{
		for (auto it = this->inputState.begin(); it != this->inputState.end(); ++it)
		{
			if (it->first == INPUT_TYPE::LEFT && it->second == true
				&& this->inputState.at(INPUT_TYPE::RIGHT) == false)
				getComposition()->sendMessage(new GameMessage::Message(GameMessage::LEFT));
			else if (it->first == INPUT_TYPE::RIGHT
				&& it->second == true && this->inputState.at(INPUT_TYPE::LEFT) == false)
				getComposition()->sendMessage(new GameMessage::Message(GameMessage::RIGHT));
			else if (it->first == INPUT_TYPE::JUMP && it->second == true)
				getComposition()->sendMessage(new GameMessage::Message(GameMessage::JUMP));
			else if (it->first == INPUT_TYPE::DEBUG && it->second == true)
			{
				if (GameTools::debugManager::getInstance().isActivateGraphic()) GameTools::debugManager::getInstance().disableGraphic();
				else GameTools::debugManager::getInstance().activateGraphic();
				it->second = false;
			}
			else if (it->first == INPUT_TYPE::ROTATE_LEFT && it->second == true) getComposition()->sendMessage(new GameMessage::Message(GameMessage::ROTATE_LEFT));
			else if (it->first == INPUT_TYPE::ROTATE_RIGHT && it->second == true) getComposition()->sendMessage(new GameMessage::Message(GameMessage::ROTATE_RIGHT));
			else if (it->first == INPUT_TYPE::FIRE && it->second == true) this->duration += (float)((this->duration + dt > 1000.0f) ? (1000.0f - this->duration) : dt);
			if (this->savedDt <= this->getComposition()->getCooldown()) this->savedDt += (float)dt;
		}
	}
	void InputComponent::setDuration(float duration)
	{
		this->duration = duration;
	}
	float InputComponent::getDuration()
	{
		return this->duration;
	}
	void InputComponent::setSavedDt(float savedDt)
	{
		this->savedDt = savedDt;
	}
	float InputComponent::getSavedDt()
	{
		return this->savedDt;
	}
	float InputComponent::getMaxElapsedTime()
	{
		return this->maxElapsedTime;
	}
}
