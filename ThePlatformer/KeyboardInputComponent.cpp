#include "KeyboardInputComponent.h"
#include "SpriteComponent.h"
#include "FireMessage.h"

namespace GameComponents {

	KeyboardInputComponent::KeyboardInputComponent(GameObjects::BaseGameObject *object, std::string inputFilename) : InputComponent(object)
	{
		this->inputFilename = inputFilename;
	}


	KeyboardInputComponent::~KeyboardInputComponent()
	{
	}

	void KeyboardInputComponent::UpdateInputState(sf::Event event, double dt)
	{
		for (auto it = this->keyboardMap.begin(); it != this->keyboardMap.end(); ++it)
		{
			if (event.type == sf::Event::KeyPressed && event.key.code == it->second) inputState.at(it->first) = true;
			else if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == it->second)
				{
					inputState.at(it->first) = false;
					switch (it->first)
					{
					case INPUT_TYPE::LEFT:
						getComposition()->sendMessage(new GameMessage::Message(GameMessage::LEFT_RELEASED));
						break;
					case INPUT_TYPE::RIGHT:
						getComposition()->sendMessage(new GameMessage::Message(GameMessage::RIGHT_RELEASED));
						break;
					default:
						break;
					}
					if (savedMessage.size() >= 10)
						savedMessage.erase(savedMessage.begin());
					savedMessage.push_back(it->first);
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == it->second) inputState.at(it->first) = true;
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
							if (this->savedDt < this->getComposition()->getCooldown()) break;
							this->composition->sendMessage(new GameMessage::FireMessage(event, this->getDuration()));
							this->setDuration(500.0f);
							this->savedDt = 0.0f;
							break;
						}
					}
					if (savedMessage.size() >= 10)
						savedMessage.erase(savedMessage.begin());
					savedMessage.push_back(it->first);
				}
			}
		}
	}

	void KeyboardInputComponent::Init()
	{
		std::string extension = inputFilename.substr(inputFilename.find_last_of(".") + 1);
		if (std::string("json").compare(extension) == 0) {
			GameSystems::JSONParser parser(inputFilename);
			ParseInputFile(parser.getJSONValue());
		}
	}

	int	KeyboardInputComponent::ParseInputFile(GameTools::JsonValue o) {
		switch (o.getTag()) {
		case GameTools::JSON_OBJECT:
			for (auto i : o) {
				printf("%s = ", i->key);
				if (std::string(i->key) == "cheat_code") ParseCheatCodeFile(i->value.toString());
				else {
					INPUT_TYPE inputKey;
					inputKey = (INPUT_TYPE)std::stoi(i->key);
					this->keyboardMap.emplace(inputKey, (int)i->value.toNumber());
					this->inputState.emplace(inputKey, false);
				}
			}
			break;
		}
		return 0;
	}

	void KeyboardInputComponent::sendMessage(GameMessage::Message *message)
	{
		switch (message->id)
		{
		case GameMessage::JUMP_RELEASED:
			inputState.at(INPUT_TYPE::JUMP) = false;
			break;
		default:
			break;
		}
	}
}
