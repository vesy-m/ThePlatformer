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

	void InputComponent::Update()
	{
		for (auto it = this->inputState.begin(); it != this->inputState.end(); ++it)
		{
			if (it->first == INPUT_TYPE::LEFT && it->second == true && this->inputState.at(INPUT_TYPE::RIGHT) == false)
			{
				//std::cout << "LEFT" << std::endl;
				getComposition()->sendMessage(new Message(Message::LEFT));
			}
			if (it->first == INPUT_TYPE::RIGHT && it->second == true && this->inputState.at(INPUT_TYPE::LEFT) == false)
			{
				//std::cout << "RIGHT" << std::endl;
				getComposition()->sendMessage(new Message(Message::RIGHT));
			}

			if (it->first == INPUT_TYPE::JUMP && it->second == true)
			{
				getComposition()->sendMessage(new Message(Message::JUMP));
				//std::cout << "JUMP" << std::endl;
			}
			if (it->first == INPUT_TYPE::DEBUG && it->second == true)
			{
				//this->composition->sendMessage(new Message(Message::SHOW_DEBUG));
				if (debugManager::getInstance().isActivateGraphic()) {
					debugManager::getInstance().disableGraphic();
				}
				else {
					debugManager::getInstance().activateGraphic();
				}
				//std::cout << "DEBUG" << std::endl;
				it->second = false;
			}
			if (it->first == INPUT_TYPE::ROTATE_LEFT && it->second == true)
			{
				getComposition()->sendMessage(new Message(Message::ROTATE_LEFT));
			}
			if (it->first == INPUT_TYPE::ROTATE_RIGHT && it->second == true)
			{
				getComposition()->sendMessage(new Message(Message::ROTATE_RIGHT));
			}
		}
	}
}
