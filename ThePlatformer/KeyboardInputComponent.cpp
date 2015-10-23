#include "KeyboardInputComponent.h"


namespace GameComponents {

	KeyboardInputComponent::KeyboardInputComponent(GameObjects::BaseGameObject *object) : InputComponent(object)
	{
	}


	KeyboardInputComponent::~KeyboardInputComponent()
	{
	}

	void KeyboardInputComponent::UpdateInputState(sf::Event event)
	{
		for (std::map<INPUT_TYPE, sf::Keyboard::Key>::iterator it = this->keyboardMap.begin(); it != this->keyboardMap.end(); ++it)
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == it->second)
				{
					inputState.at(it->first) = true;
				}
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == it->second)
				{
					inputState.at(it->first) = false;
					switch (it->first)
					{
					case INPUT_TYPE::LEFT:
						getComposition()->sendMessage(new Message(Message::LEFT_RELEASED));
						break;

					case INPUT_TYPE::RIGHT:
						getComposition()->sendMessage(new Message(Message::RIGHT_RELEASED));
						break;

					default:
						break;
					}
				}
			}
		}
	}

	void KeyboardInputComponent::Init()
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
	void KeyboardInputComponent::sendMessage(Message *message)
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
}
