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

	void InputComponent::Update()
	{
		for (std::map<INPUT_TYPE, bool>::iterator it = this->inputState.begin(); it != this->inputState.end(); ++it)
		{
			if (it->first == INPUT_TYPE::LEFT && it->second == true && this->inputState.at(INPUT_TYPE::RIGHT) == false)
			{
				//std::cout << "LEFT" << std::endl;
				this->composition->sendMessage(new Message(Message::LEFT));
			}
			if (it->first == INPUT_TYPE::RIGHT && it->second == true && this->inputState.at(INPUT_TYPE::LEFT) == false)
			{
				//std::cout << "RIGHT" << std::endl;
				this->composition->sendMessage(new Message(Message::RIGHT));
			}

			if (it->first == INPUT_TYPE::JUMP && it->second == true)
			{
				this->composition->sendMessage(new Message(Message::JUMP));
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
				this->composition->sendMessage(new Message(Message::ROTATE_LEFT));
			}
			if (it->first == INPUT_TYPE::ROTATE_RIGHT && it->second == true)
			{
				this->composition->sendMessage(new Message(Message::ROTATE_RIGHT));
			}
		}
	}

	void InputComponent::UpdateInputState(sf::Event event)
	{
		for (std::map<INPUT_TYPE, sf::Keyboard::Key>::iterator it = this->keyboardMap.begin(); it != this->keyboardMap.end(); ++it)
		{
			if(event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == it->second)
				{
					inputState.at(it->first) = true;
				}
			}
			else if(event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == it->second)
				{
					inputState.at(it->first) = false;
					switch (it->first)
					{
						case INPUT_TYPE::LEFT:
							this->composition->sendMessage(new Message(Message::LEFT_RELEASED));
							break;

						case INPUT_TYPE::RIGHT:
							this->composition->sendMessage(new Message(Message::RIGHT_RELEASED));
							break;

						default:
							break;
					}
				}
			}
		}
	}

	void InputComponent::Init()
	{
		this->keyboardMap.emplace(LEFT, sf::Keyboard::Q);
		this->keyboardMap.emplace(RIGHT, sf::Keyboard::D);
		this->keyboardMap.emplace(JUMP, sf::Keyboard::Space);
		this->keyboardMap.emplace(DEBUG, sf::Keyboard::F5);
		this->keyboardMap.emplace(ROTATE_LEFT, sf::Keyboard::L);
		this->keyboardMap.emplace(ROTATE_RIGHT, sf::Keyboard::M);


		this->inputState.emplace(LEFT, false);
		this->inputState.emplace(RIGHT, false);
		this->inputState.emplace(JUMP, false);
		this->inputState.emplace(DEBUG, false);
		this->inputState.emplace(ROTATE_LEFT, false);
		this->inputState.emplace(ROTATE_RIGHT, false);



		this->mouseMap.emplace(FIRE, sf::Mouse::Left);
		this->mouseMap.emplace(SPECIAL, sf::Mouse::Right);
	}

	void InputComponent::sendMessage(Message* message)
	{
		switch (message->id)
		{
		case Message::JUMP_RELEASED:
			inputState.at(INPUT_TYPE::JUMP) = false;
			break;
		default:
			break;
		}
	}

	void InputComponent::setKeyboardKey(INPUT_TYPE inputType, sf::Keyboard::Key key)
	{
		std::map<INPUT_TYPE, sf::Keyboard::Key>::iterator it = this->keyboardMap.find(inputType);
		it->second = key;
	}

	void InputComponent::setMouseButton(INPUT_TYPE inputType, sf::Mouse::Button button)
	{
		std::map<INPUT_TYPE, sf::Mouse::Button>::iterator it = this->mouseMap.find(inputType);
		it->second = button;
	}
}
