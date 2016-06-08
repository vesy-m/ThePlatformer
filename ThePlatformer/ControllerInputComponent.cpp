#include "ControllerInputComponent.h"


namespace GameComponents {

	ControllerInputComponent::ControllerInputComponent(GameObjects::BaseGameObject *object, const std::string &filename, int idController) : InputComponent(object)
	{
		this->filename = filename;
		this->controllerNumber = idController;
		this->idController = idController;
	}


	ControllerInputComponent::~ControllerInputComponent()
	{
	}

	void ControllerInputComponent::UpdateInputState(sf::Event event, double)
	{
		if ((event.joystickButton.joystickId != controllerNumber) || (event.joystickMove.joystickId != controllerNumber)) return;
		for (auto it = this->controllerMap.begin(); it != this->controllerMap.end(); ++it)
		{
			if (event.type == sf::Event::JoystickButtonPressed)
			{
				if (event.joystickButton.button == it->second)
					inputState.at(it->first) = true;
			}
			else if (event.type == sf::Event::JoystickButtonReleased)
			{
				if (event.joystickButton.button == it->second)
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
					case INPUT_TYPE::ATTACK1:
						if (attack_1 == 0)
						{
							attack_1 = this->composition->getAttack1Value();
							this->composition->sendMessage(new GameMessage::Message(GameMessage::ATTACK1));
						}
						break;
					case INPUT_TYPE::ATTACK2:
						if (attack_2 == 0) {
							attack_2 = this->composition->getAttack2Value();
							this->composition->sendMessage(new GameMessage::Message(GameMessage::ATTACK2));
						}
						break;
					case INPUT_TYPE::ATTACK3:
						if (attack_3 == 0) {
							this->attack_3 = this->composition->getAttack3Value();
							if (this->composition->getName().find("baseballPlayer") != std::string::npos)
								this->composition->sendMessage(new GameMessage::Message(GameMessage::ATTACK3_RELEASED));
							else
								this->composition->sendMessage(new GameMessage::Message(GameMessage::ATTACK3));
						}
						break;
					}
					if (savedMessage.size() >= 10)
						savedMessage.erase(savedMessage.begin());
					savedMessage.push_back(it->first);
				}
			}
			else if (event.type == sf::Event::JoystickMoved)
			{
				if (DetectAxisInput(event, it->second) && CheckInputValue(event, it->second))
					inputState.at(it->first) = true;
				else if (DetectAxisInput(event, it->second))
				{
					if (inputState.at(it->first) == true)
					{
						inputState.at(it->first) = false;
						if (it->first == INPUT_TYPE::RIGHT)
							getComposition()->sendMessage(new GameMessage::Message(GameMessage::RIGHT_RELEASED));
						else if(it->first == INPUT_TYPE::LEFT)
							getComposition()->sendMessage(new GameMessage::Message(GameMessage::LEFT_RELEASED));
						if (savedMessage.size() >= 10)
							savedMessage.erase(savedMessage.begin());
						savedMessage.push_back(it->first);
					}
				}
			}
		}
	}

	bool ControllerInputComponent::DetectAxisInput(sf::Event event, int button)
	{
		if ((event.joystickMove.axis == sf::Joystick::X || event.joystickMove.axis == sf::Joystick::PovX) && button >= 50 && button <= 53) return true;
		else if (event.joystickMove.axis == sf::Joystick::U) {
			aimAxisX = event.joystickMove.position;
			return false;
		}
		else if (event.joystickMove.axis == sf::Joystick::R) {
			aimAxisY = event.joystickMove.position;
			return false;
		}
		else if (event.joystickMove.axis == sf::Joystick::Z && (button == 70 || button == 71)) return true;
		else return false;
	}

	bool ControllerInputComponent::CheckInputValue(sf::Event event, int button)
	{
		switch (button)
		{
		case 52:
			if (event.joystickMove.position <= -78) return true;
			break;
		case 51:
			if (event.joystickMove.position >= 78) return true;
			break;
		case 62:
			if (event.joystickMove.position <= -98) return true;
			break;
		case 61:
			if (event.joystickMove.position >= 98) return true;
			break;
		case 71:
			if (event.joystickMove.position <= -98) return true;
			break;
		case 70:
			if (event.joystickMove.position >= 98) return true;
			break;
		default:
			break;
		}
		return false;
	}

	void ControllerInputComponent::Init()
	{
		aimAxisX = 0.0;
		aimAxisY = 0.0;
		std::string extension = filename.substr(filename.find_last_of(".") + 1);
		if (std::string("json").compare(extension) == 0) {
			GameSystems::JSONParser parser(filename);
			ParseInputFile(parser.getJSONValue());
		}
	}

	int	ControllerInputComponent::ParseInputFile(GameTools::JsonValue o) {
		switch (o.getTag()) {
		case GameTools::JSON_OBJECT:
			for (auto i : o) {
				printf("%s = ", i->key);
				if (std::string(i->key) == "cheat_code") ParseCheatCodeFile(i->value.toString());
				else {
					INPUT_TYPE inputKey;
					inputKey = (INPUT_TYPE)std::stoi(i->key);
					this->controllerMap.emplace(inputKey, (int)i->value.toNumber());
					this->inputState.emplace(inputKey, false);
				}
			}
			break;
		}
		return 0;
	}

	void ControllerInputComponent::sendMessage(GameMessage::Message* message)
	{
		switch (message->id)
		{
		case GameMessage::JUMP_RELEASED:
			inputState.at(INPUT_TYPE::JUMP) = false;
			break;
		case GameMessage::STOP_DASH:
		case GameMessage::STOP_BLOCK:
			this->attack_3 = this->composition->getAttack3Value();
			break;
		default:
			break;
		}
	}
}
