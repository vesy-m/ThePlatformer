#include "InputComponent.h"

namespace GameComponents {

	InputComponent::InputComponent(GameObjects::BaseGameObject *object) : BaseComponent(object)
	{
	}

	InputComponent::~InputComponent()
	{
	}

	COMPONENT_TYPE InputComponent::getType()
	{
		return this->componentType;
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
				getComposition()->sendMessage(new Message(Message::LEFT));
			else if (it->first == INPUT_TYPE::RIGHT
				&& it->second == true && this->inputState.at(INPUT_TYPE::LEFT) == false)
				getComposition()->sendMessage(new Message(Message::RIGHT));
			else if (it->first == INPUT_TYPE::JUMP && it->second == true)
				getComposition()->sendMessage(new Message(Message::JUMP));
			else if (it->first == INPUT_TYPE::DEBUG && it->second == true)
			{
				//this->composition->sendMessage(new Message(Message::SHOW_DEBUG));
				if (debugManager::getInstance().isActivateGraphic()) debugManager::getInstance().disableGraphic();
				else debugManager::getInstance().activateGraphic();
				it->second = false;
			}
			else if (it->first == INPUT_TYPE::ROTATE_LEFT && it->second == true)	getComposition()->sendMessage(new Message(Message::ROTATE_LEFT));
			else if (it->first == INPUT_TYPE::ROTATE_RIGHT && it->second == true) getComposition()->sendMessage(new Message(Message::ROTATE_RIGHT));
			else if (it->first == INPUT_TYPE::FIRE && it->second == true) getComposition()->sendMessage(new Message(Message::FIRE));
		}
	}
}
