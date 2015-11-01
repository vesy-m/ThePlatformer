#include "JoystickInputComponent.h"


namespace GameComponents {

	JoystickInputComponent::JoystickInputComponent(GameObjects::BaseGameObject *object, std::string filename) : InputComponent(object)
	{
		this->filename = filename;
	}


	JoystickInputComponent::~JoystickInputComponent()
	{
	}

	void JoystickInputComponent::UpdateInputState(sf::Event event)
	{
		for (auto it = this->joystickMap.begin(); it != this->joystickMap.end(); ++it)
		{
			if (event.type == sf::Event::JoystickButtonPressed)
			{
				if (event.joystickButton.button == it->second)
				{
					inputState.at(it->first) = true;
				}
			}
			else if (event.type == sf::Event::JoystickButtonReleased)
			{
				if (event.key.code == it->second)
				{
					inputState.at(it->first) = false;
				}
			}
			else if (event.type == sf::Event::JoystickMoved)
			{
				if (DetectAxisInput(event, it->second) && CheckInputValue(event, it->second))
				{
					inputState.at(it->first) = true;
				}
				else if (DetectAxisInput(event, it->second))
				{
					if (inputState.at(it->first) == true)
					{
						inputState.at(it->first) = false;
						if (it->first == INPUT_TYPE::RIGHT)
							getComposition()->sendMessage(new Message(Message::RIGHT_RELEASED));
						else if(it->first == INPUT_TYPE::LEFT)
							getComposition()->sendMessage(new Message(Message::LEFT_RELEASED));
					}
				}
			}
		}
	}

	bool JoystickInputComponent::DetectAxisInput(sf::Event event, int button)
	{
		if (event.joystickMove.axis == sf::Joystick::X && button >= 50 && button <= 53)
			return true;
		else if (event.joystickMove.axis == sf::Joystick::U && button >= 60 && button <= 63)
			return true;
		else if (event.joystickMove.axis == sf::Joystick::Z && (button == 70 || button == 71))
			return true;
		else
			return false;
	}

	bool JoystickInputComponent::CheckInputValue(sf::Event event, int button)
	{
		switch (button)
		{
		case 52:
			if (event.joystickMove.position <= -98)
				return true;
			break;
		case 51:
			if (event.joystickMove.position >= 98)
				return true;
			break;
		case 62:
			if (event.joystickMove.position <= -98)
				return true;
			break;
		case 61:
			if (event.joystickMove.position >= 98)
				return true;
			break;
		case 71:
			if (event.joystickMove.position <= -98)
				return true;
			break;
		case 70:
			if (event.joystickMove.position >= 98)
				return true;
			break;
		default:
			break;
		}
		return false;
	}

	void JoystickInputComponent::Init()
	{
		std::string extension = filename.substr(filename.find_last_of(".") + 1);
		if (std::string("json").compare(extension) == 0) {
			GameSystems::JSONParser parser(filename);
			ParseInputFile(parser.getJSONValue());
		}

		/*this->joystickMap.emplace(LEFT, 52);
		this->joystickMap.emplace(RIGHT, 51);
		this->joystickMap.emplace(JUMP, 0);
		this->joystickMap.emplace(DEBUG, 6);
		this->joystickMap.emplace(ROTATE_LEFT, sf::Keyboard::L);
		this->joystickMap.emplace(ROTATE_RIGHT, sf::Keyboard::M);*/


		this->inputState.emplace(LEFT, false);
		this->inputState.emplace(RIGHT, false);
		this->inputState.emplace(JUMP, false);
		this->inputState.emplace(DEBUG, false);
		this->inputState.emplace(ROTATE_LEFT, false);
		this->inputState.emplace(ROTATE_RIGHT, false);
	}

	int	JoystickInputComponent::ParseInputFile(JsonValue o) {
		switch (o.getTag()) {
		case JSON_OBJECT:
			for (auto i : o) {
				printf("%s = ", i->key);
				INPUT_TYPE inputKey;
				inputKey = (INPUT_TYPE)std::stoi(i->key);
				this->joystickMap.emplace(inputKey, (int)i->value.toNumber());
			}
			break;
		}
		return 0;
	}

	void JoystickInputComponent::sendMessage(Message* message)
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
