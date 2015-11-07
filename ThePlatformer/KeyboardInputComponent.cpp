#include "KeyboardInputComponent.h"


namespace GameComponents {

	KeyboardInputComponent::KeyboardInputComponent(GameObjects::BaseGameObject *object, std::string filename) : InputComponent(object)
	{
		this->filename = filename;
	}


	KeyboardInputComponent::~KeyboardInputComponent()
	{
	}

	void KeyboardInputComponent::UpdateInputState(sf::Event event, double dt)
	{
		static float duration = 500.0f;
		for (auto it = this->keyboardMap.begin(); it != this->keyboardMap.end(); ++it)
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == it->second) inputState.at(it->first) = true;
				//if (it->first == INPUT_TYPE::FIRE) duration += (float)((duration + dt > 1000.0f) ? (1000.0f - duration) : dt);
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == it->second)
				{
					inputState.at(it->first) = false;
					switch (it->first)
					{
					case INPUT_TYPE::LEFT:
						getComposition()->sendMessage(new GameMessage::Message(GameMessage::Message::LEFT_RELEASED));
						break;
					case INPUT_TYPE::RIGHT:
						getComposition()->sendMessage(new GameMessage::Message(GameMessage::Message::RIGHT_RELEASED));
						break;
					/*case INPUT_TYPE::FIRE:
					{
						GameObjects::BaseGameObject *arrow = GameSystems::ObjectFactory::getInstance().createArrow(getComposition()->getX() + 35, getComposition()->getY(), duration);
						duration = 500.0f;
						break;
					}*/
					default:
						break;
					}
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == it->second) inputState.at(it->first) = true;
				if (it->first == INPUT_TYPE::FIRE) {
					duration += (float)((duration + dt > 1000.0f) ? (1000.0f - duration) : dt);
					std::cout << "Duration: " << duration << std::endl;
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.key.code == it->second)
				{
					inputState.at(it->first) = false;
					switch (it->first)
					{
					case INPUT_TYPE::FIRE:
					{
						std::cout << "mouse x: " << event.mouseButton.x << std::endl;
						std::cout << "mouse y: " << event.mouseButton.y << std::endl;
						GameObjects::BaseGameObject *arrow = GameSystems::ObjectFactory::getInstance().createArrow(getComposition()->getX() + 35, getComposition()->getY(), duration);
						duration = 500.0f;
						break;
					}
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

	void KeyboardInputComponent::sendMessage(GameMessage::Message *message)
	{
		switch (message->id)
		{
		case GameMessage::Message::JUMP_RELEASED:
			inputState.at(INPUT_TYPE::JUMP) = false;
			break;
		default:
			break;
		}
	}
}
