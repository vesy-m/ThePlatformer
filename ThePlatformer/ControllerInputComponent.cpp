#include "ControllerInputComponent.h"


namespace GameComponents {

	ControllerInputComponent::ControllerInputComponent(GameObjects::BaseGameObject *object, std::string filename) : InputComponent(object)
	{
		this->filename = filename;
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
					if (it->first == INPUT_TYPE::FIRE) {
						GLint iViewport[4];
						glGetIntegerv(GL_VIEWPORT, iViewport);
						int screenWidth = iViewport[0] + iViewport[2];
						int screenHeight = iViewport[1] + iViewport[3];
						int resolutionWidth = GameSystems::GraphicsSystem::Camera::getInstance().resolutionWidth;
						int resolutionHeight = GameSystems::GraphicsSystem::Camera::getInstance().resolutionHeight;

						int centerX = (this->getComposition()->getX() + (this->getComposition()->getWidth() / 2)) * screenWidth / resolutionWidth;
						int centerY = (this->getComposition()->getY() + (this->getComposition()->getHeight() / 2)) * screenHeight / resolutionHeight;
						GameComponents::SpriteComponent *sprite = reinterpret_cast<GameComponents::SpriteComponent*>(getComposition()->getComponent(GameComponents::SPRITE));

						glm::vec2 direction = glm::vec2(100.0, 100.0);
						if (aimAxisX >= -50.0 && aimAxisX <= 50.0 && aimAxisY >= -50.0 && aimAxisY <= 50.0) {
							if (sprite->revertX)
								direction = glm::vec2((-100 + centerX) - centerX, (aimAxisY + centerY) - centerY);
							else
								direction = glm::vec2((100 + centerX) - centerX, (aimAxisY + centerY) - centerY);
						}
						else
							direction = glm::vec2((aimAxisX + centerX) - centerX, (aimAxisY + centerY) - centerY);
						std::cout << "Duration: " << this->getDuration() << std::endl;
						GameObjects::BaseGameObject *arrow = GameSystems::ObjectFactory::getInstance().createArrow(getComposition(), getComposition()->getX(),
							getComposition()->getY(), this->getDuration(), glm::normalize(direction));
						this->setDuration(500.0f);
					}
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
							getComposition()->sendMessage(new GameMessage::Message(GameMessage::Message::RIGHT_RELEASED));
						else if(it->first == INPUT_TYPE::LEFT)
							getComposition()->sendMessage(new GameMessage::Message(GameMessage::Message::LEFT_RELEASED));
						else if (it->first == INPUT_TYPE::FIRE) {
							int centerX = this->getComposition()->getX() + (this->getComposition()->getHeight() / 2);
							int centerY = this->getComposition()->getY() + (this->getComposition()->getHeight() / 2);
							GameComponents::SpriteComponent *sprite = reinterpret_cast<GameComponents::SpriteComponent*>(getComposition()->getComponent(GameComponents::SPRITE));

							glm::vec2 direction = glm::vec2(100.0, 100.0);
							if (aimAxisX >= -50.0 && aimAxisX <= 50.0 && aimAxisY >= -50.0 && aimAxisY <= 50.0) {
								if (sprite->revertX) direction = glm::vec2((-100 + centerX) - centerX, (aimAxisY + centerY) - centerY);
								else direction = glm::vec2((100 + centerX) - centerX, (aimAxisY + centerY) - centerY);
							}
							else direction = glm::vec2((aimAxisX + centerX) - centerX, (aimAxisY + centerY) - centerY);

							std::cout << "Duration: " << this->getDuration() << std::endl;
							GameObjects::BaseGameObject *arrow = GameSystems::ObjectFactory::getInstance().createArrow(getComposition(), getComposition()->getX(),
								getComposition()->getY(), this->getDuration(), glm::normalize(direction));
							this->setDuration(500.0f);
						}
					}
				}
			}
		}
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
			if (event.joystickMove.position <= -98) return true;
			break;
		case 51:
			if (event.joystickMove.position >= 98) return true;
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
		controllerNumber = 0;
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
				if (std::string(i->key) == "controller") controllerNumber = (int)i->value.toNumber();
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
		case GameMessage::Message::JUMP_RELEASED:
			inputState.at(INPUT_TYPE::JUMP) = false;
			break;
		default:
			break;
		}
	}
}
