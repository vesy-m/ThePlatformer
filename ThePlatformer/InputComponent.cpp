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
			if (it->first == LEFT && it->second == true)
			{
				std::cout << "LEFT" << std::endl;
				this->composition->SendMessage(new Message(Message::LEFT));
				this->composition->setX(this->composition->getX() - 3);
			}
			if (it->first == RIGHT && it->second == true)
			{
				std::cout << "RIGHT" << std::endl;
				this->composition->SendMessage(new Message(Message::RIGHT));
				this->composition->setX(this->composition->getX() + 3);

			}

			if (it->first == JUMP && it->second == true)
			{
				this->composition->SendMessage(new Message(Message::JUMP));
				std::cout << "JUMP" << std::endl;
			}
		}
	}

	void InputComponent::UpdateInputState(sf::Event event)
	{
		for (std::map<INPUT_TYPE, sf::Keyboard::Key>::iterator it = this->keyboardMap.begin(); it != this->keyboardMap.end(); ++it)
		{
			if(event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == it->second /*sf::Keyboard::isKeyPressed(it->second)*/)
				{
					inputState.at(it->first) = true;
				}
			}
			else if(event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == it->second /*sf::Keyboard::isKeyPressed(it->second)*/)
				{
					inputState.at(it->first) = false;
					this->composition->SendMessage(new Message(Message::DEFAULT));
				}
			}
		}

		//for (std::map<INPUT_TYPE, sf::Mouse::Button>::iterator it = this->mouseMap.begin(); it != this->mouseMap.end(); ++it)
		//{
		//	if (sf::Mouse::isButtonPressed(it->second) && it->first == FIRE)
		//	{
		//		std::cout << "FIRE" << std::endl;
		//	}
		//	if (sf::Mouse::isButtonPressed(it->second) && it->first == SPECIAL)
		//	{
		//		std::cout << "SPECIAL" << std::endl;
		//	}
		//}
	}

	void InputComponent::Init()
	{
		this->keyboardMap.emplace(LEFT, sf::Keyboard::Q);
		this->keyboardMap.emplace(RIGHT, sf::Keyboard::D);
		this->keyboardMap.emplace(JUMP, sf::Keyboard::Space);

		this->inputState.emplace(LEFT, false);
		this->inputState.emplace(RIGHT, false);
		this->inputState.emplace(JUMP, false);

		this->mouseMap.emplace(FIRE, sf::Mouse::Left);
		this->mouseMap.emplace(SPECIAL, sf::Mouse::Right);
	}

	void InputComponent::sendMessage(Message*)
	{
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
