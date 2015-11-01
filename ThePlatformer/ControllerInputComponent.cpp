#include "ControllerInputComponent.h"


namespace GameComponents {

	ControllerInputComponent::ControllerInputComponent(GameObjects::BaseGameObject *object, std::string filename) : InputComponent(object)
	{
		this->filename = filename;
	}


	ControllerInputComponent::~ControllerInputComponent()
	{
	}

	void ControllerInputComponent::UpdateInputState(sf::Event event)
	{
		for (auto it = this->controllerMap.begin(); it != this->controllerMap.end(); ++it)
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

	bool ControllerInputComponent::DetectAxisInput(sf::Event event, int button)
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

	bool ControllerInputComponent::CheckInputValue(sf::Event event, int button)
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

	void ControllerInputComponent::Init()
	{
		std::string extension = filename.substr(filename.find_last_of(".") + 1);
		if (std::string("json").compare(extension) == 0) {
			GameSystems::JSONParser parser(filename);
			ParseInputFile(parser.getJSONValue());
		}

		this->inputState.emplace(LEFT, false);
		this->inputState.emplace(RIGHT, false);
		this->inputState.emplace(JUMP, false);
		this->inputState.emplace(DEBUG, false);
		this->inputState.emplace(ROTATE_LEFT, false);
		this->inputState.emplace(ROTATE_RIGHT, false);
	}

	int	ControllerInputComponent::ParseInputFile(JsonValue o) {
		switch (o.getTag()) {
		case JSON_OBJECT:
			for (auto i : o) {
				printf("%s = ", i->key);
				INPUT_TYPE inputKey;
				inputKey = (INPUT_TYPE)std::stoi(i->key);
				this->controllerMap.emplace(inputKey, (int)i->value.toNumber());
			}
			break;
		}
		return 0;
	}

	void ControllerInputComponent::sendMessage(Message* message)
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
