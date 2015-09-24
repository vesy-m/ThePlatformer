#include "InputComponent.h"

namespace GameComponents {

	InputComponent::InputComponent(COMPONENT_TYPE componentType)
	{
		this->componentType = componentType;

		this->inputMap[LEFT] = sf::Keyboard::Q;
		this->inputMap[RIGHT] = sf::Keyboard::D;
		this->inputMap[JUMP] = sf::Keyboard::Space;
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
		for (std::map<INPUT_TYPE, sf::Keyboard::Key>::iterator it = inputMap.begin(); it != inputMap.end(); ++it)
		{
			if (sf::Keyboard::isKeyPressed(it->second) && it->first == LEFT)
			{
				std::cout << "LEFT" << std::endl;
			}
			if (sf::Keyboard::isKeyPressed(it->second) && it->first == RIGHT)
			{
				std::cout << "RIGHT" << std::endl;
			}
			if (sf::Keyboard::isKeyPressed(it->second) && it->first == JUMP)
			{
				std::cout << "JUMP" << std::endl;
			}
		}
	}

	void InputComponent::Init()
	{
	}
}
