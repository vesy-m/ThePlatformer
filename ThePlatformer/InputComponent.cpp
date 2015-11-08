#include "InputComponent.h"

namespace GameComponents {

	InputComponent::InputComponent(GameObjects::BaseGameObject *object) : BaseComponent(object)
	{
		object->attachComponent(this);
		this->duration = 250.0f;
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
				getComposition()->sendMessage(new GameMessage::Message(GameMessage::Message::LEFT));
			else if (it->first == INPUT_TYPE::RIGHT
				&& it->second == true && this->inputState.at(INPUT_TYPE::LEFT) == false)
				getComposition()->sendMessage(new GameMessage::Message(GameMessage::Message::RIGHT));
			else if (it->first == INPUT_TYPE::JUMP && it->second == true)
				getComposition()->sendMessage(new GameMessage::Message(GameMessage::Message::JUMP));
			else if (it->first == INPUT_TYPE::DEBUG && it->second == true)
			{
				//this->composition->sendMessage(new Message(Message::SHOW_DEBUG));
				if (debugManager::getInstance().isActivateGraphic()) debugManager::getInstance().disableGraphic();
				else debugManager::getInstance().activateGraphic();
				it->second = false;
			}
			else if (it->first == INPUT_TYPE::ROTATE_LEFT && it->second == true)	getComposition()->sendMessage(new GameMessage::Message(GameMessage::Message::ROTATE_LEFT));
			else if (it->first == INPUT_TYPE::ROTATE_RIGHT && it->second == true) getComposition()->sendMessage(new GameMessage::Message(GameMessage::Message::ROTATE_RIGHT));
			else if (it->first == INPUT_TYPE::FIRE && it->second == true)
				this->duration += (float)((this->duration + dt > 1000.0f) ? (1000.0f - this->duration) : dt);
				//getComposition()->sendMessage(new GameMessage::Message(GameMessage::Message::FIRE));
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
}
