#include "ControllerInputComponent.h"


namespace GameComponents {

	ControllerInputComponent::ControllerInputComponent(GameObjects::BaseGameObject *object, const std::string &filename, int idController) : InputComponent(object)
	{
		this->filename = filename;
		this->controllerNumber = idController;
	}


	ControllerInputComponent::~ControllerInputComponent()
	{
	}

	void ControllerInputComponent::UpdateInputState(sf::Event event, double)
	{
		if ((event.joystickButton.joystickId != controllerNumber) || (event.joystickMove.joystickId != controllerNumber))
			return;
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
				if (event.joystickButton.button == it->second)
				{
					inputState.at(it->first) = false;
					switch (it->first)
					{
					case INPUT_TYPE::FIRE:
					{
						if (this->savedDt < this->getComposition()->getCooldown())
							break;

						int centerX = (this->getComposition()->getX() + (this->getComposition()->getWidth() / 2));
						int centerY = (this->getComposition()->getY() + (this->getComposition()->getHeight() / 2));
						GameComponents::SpriteComponent *sprite = reinterpret_cast<GameComponents::SpriteComponent*>(getComposition()->getComponent(GameComponents::SPRITE));

						glm::vec2 direction = glm::vec2(100.0, 100.0);
						if (aimAxisX >= -50.0 && aimAxisX <= 50.0 && aimAxisY >= -50.0 && aimAxisY <= 50.0) {
							if (sprite->revertX) direction = glm::vec2((-100 + centerX) - centerX, (-70 + centerY) - centerY);
							else direction = glm::vec2((100 + centerX) - centerX, (-70 + centerY) - centerY);
						}
						else direction = glm::vec2((aimAxisX + centerX) - centerX, (aimAxisY + centerY) - centerY);

						GameObjects::BaseGameObject *arrow = GameSystems::ObjectFactory::getInstance().createProjectile(getComposition(), getComposition()->getX(),
							getComposition()->getY(), this->getDuration(), glm::normalize(direction), GameSystems::ObjectFactory::SOCCER_BALL);
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
							getComposition()->sendMessage(new GameMessage::Message(GameMessage::RIGHT_RELEASED));
						else if(it->first == INPUT_TYPE::LEFT)
							getComposition()->sendMessage(new GameMessage::Message(GameMessage::LEFT_RELEASED));
						else if (it->first == INPUT_TYPE::FIRE) {
							int centerX = this->getComposition()->getX() + (this->getComposition()->getHeight() / 2);
							int centerY = this->getComposition()->getY() + (this->getComposition()->getHeight() / 2);
							GameComponents::SpriteComponent *sprite = reinterpret_cast<GameComponents::SpriteComponent*>(getComposition()->getComponent(GameComponents::SPRITE));

							glm::vec2 direction = glm::vec2(100.0, 100.0);
							if (aimAxisX >= -50.0 && aimAxisX <= 50.0 && aimAxisY >= -50.0 && aimAxisY <= 50.0) {
								if (sprite->revertX) direction = glm::vec2((-100 + centerX) - centerX, (-100 + centerY) - centerY);
								else direction = glm::vec2((100 + centerX) - centerX, (-100 + centerY) - centerY);
							}
							else direction = glm::vec2((aimAxisX + centerX) - centerX, (aimAxisY + centerY) - centerY);

							std::cout << "Duration: " << this->getDuration() << std::endl;
							GameObjects::BaseGameObject *arrow = GameSystems::ObjectFactory::getInstance().createProjectile(getComposition(), getComposition()->getX(),
								getComposition()->getY(), this->getDuration(), glm::normalize(direction), GameSystems::ObjectFactory::SOCCER_BALL);
							this->setDuration(500.0f);
						}
						if (savedMessage.size() >= 10)
							savedMessage.erase(savedMessage.begin());
						savedMessage.push_back(it->first);
					}
				}
			}
		}
		glm::vec2 direction;
		glm::vec2 aimAxis = glm::vec2(aimAxisX, aimAxisY);
		GameComponents::SpriteComponent *sprite = reinterpret_cast<GameComponents::SpriteComponent*>(getComposition()->getComponent(GameComponents::SPRITE));

		//std::cout << "AimAxis X: " << aimAxisX << std::endl;

		if ((sprite->revertX && aimAxisX > 0.0f && aimAxisX <= 0.05f) ||
			(!sprite->revertX && aimAxisX < 0.0f && aimAxisX >= -0.05f)) {
			//std::cout << "Direction Change" << std::endl;
			aimAxisX *= -1;
		} else
			//std::cout << "XXXX" << std::endl;

		if (aimAxisX == 0.0f && aimAxisY == 0.0f) direction = aimAxis;
		else direction = glm::normalize(aimAxis);


		//std::cout << "aimAxisX x: " << aimAxisX << "\t" << "aimAxisY y: " << aimAxisY << std::endl;

		this->composition->sendMessage(new GameMessage::AimMessage(direction));
	}

	bool ControllerInputComponent::DetectAxisInput(sf::Event event, int button)
	{
		if (event.joystickMove.axis == sf::Joystick::X && button >= 50 && button <= 53) return true;
		else if (event.joystickMove.axis == sf::Joystick::U) {
			aimAxisX = event.joystickMove.position;
			return false;
		}
		else if (event.joystickMove.axis == sf::Joystick::R) {
			aimAxisY = event.joystickMove.position;
			return false;
		}
		//else if (event.joystickMove.axis == sf::Joystick::U && button >= 60 && button <= 63) return true;
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
		//controllerNumber = 0;
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
				//if (std::string(i->key) == "controller") controllerNumber = (int)i->value.toNumber();
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
		default:
			break;
		}
	}
}
