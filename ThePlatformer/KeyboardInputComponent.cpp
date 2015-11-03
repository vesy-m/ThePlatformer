#include "KeyboardInputComponent.h"


namespace GameComponents {

	KeyboardInputComponent::KeyboardInputComponent(GameObjects::BaseGameObject *object, std::string filename) : InputComponent(object)
	{
		this->filename = filename;
	}


	KeyboardInputComponent::~KeyboardInputComponent()
	{
	}

	void KeyboardInputComponent::UpdateInputState(sf::Event event)
	{
		for (auto it = this->keyboardMap.begin(); it != this->keyboardMap.end(); ++it)
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
					case INPUT_TYPE::FIRE:
					{
						GameObjects::BaseGameObject *arrow = GameSystems::ObjectFactory::createArrow(getComposition()->getX() + 35, getComposition()->getY());
						arrow->sendMessage(new Message(Message::FIRE));
						break;
					}
					default:
						break;
					}
				}
			}
		}
	}

	void KeyboardInputComponent::Init()
	{
		std::string extension = filename.substr(filename.find_last_of(".") + 1);
		if (std::string("json").compare(extension) == 0) {
			GameSystems::JSONParser parser(filename);
			ParseInputFile(parser.getJSONValue());
		}

		//this->mouseMap.emplace(FIRE, sf::Mouse::Left);
		this->mouseMap.emplace(SPECIAL, sf::Mouse::Right);
	}

	int	KeyboardInputComponent::ParseInputFile(JsonValue o) {
		switch (o.getTag()) {
		case JSON_OBJECT:
			for (auto i : o) {
				printf("%s = ", i->key);
				INPUT_TYPE inputKey;
				inputKey = (INPUT_TYPE)std::stoi(i->key);
				this->keyboardMap.emplace(inputKey, (int)i->value.toNumber());
				this->inputState.emplace(inputKey, false);
			}
			break;
		}
		return 0;
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
