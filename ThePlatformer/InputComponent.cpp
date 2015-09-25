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
		for (std::map<INPUT_TYPE, sf::Keyboard::Key>::iterator it = this->keyboardMap.begin(); it != this->keyboardMap.end(); ++it)
		{
			if (sf::Keyboard::isKeyPressed(it->second) && it->first == LEFT)
			{
				std::cout << "LEFT" << std::endl;
				this->composition->setX(this->composition->getX() - 1);
			}
			if (sf::Keyboard::isKeyPressed(it->second) && it->first == RIGHT)
			{
				std::cout << "RIGHT" << std::endl;
				this->composition->setX(this->composition->getX() + 1);
			}
			if (sf::Keyboard::isKeyPressed(it->second) && it->first == JUMP)
			{
				std::cout << "JUMP" << std::endl;
			}
		}

		for (std::map<INPUT_TYPE, sf::Mouse::Button>::iterator it = this->mouseMap.begin(); it != this->mouseMap.end(); ++it)
		{
			if (sf::Mouse::isButtonPressed(it->second) && it->first == FIRE)
			{
				std::cout << "FIRE" << std::endl;
			}
			if (sf::Mouse::isButtonPressed(it->second) && it->first == SPECIAL)
			{
				std::cout << "SPECIAL" << std::endl;
			}
		}
	}

	void InputComponent::Init()
	{
		this->keyboardMap.emplace(LEFT, sf::Keyboard::Q);
		this->keyboardMap.emplace(RIGHT, sf::Keyboard::D);
		this->keyboardMap.emplace(JUMP, sf::Keyboard::Space);

		this->mouseMap.emplace(FIRE, sf::Mouse::Left);
		this->mouseMap.emplace(SPECIAL, sf::Mouse::Right);
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
