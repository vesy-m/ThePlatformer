#include "KeyboardInputComponent.h"
#include "SpriteComponent.h"

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
		//static float duration = 250.0f;
		for (auto it = this->keyboardMap.begin(); it != this->keyboardMap.end(); ++it)
		{
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == it->second) inputState.at(it->first) = true;
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
					default:
						break;
					}
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
						GLint iViewport[4];
						glGetIntegerv(GL_VIEWPORT, iViewport);
						int screenWidth = iViewport[0] + iViewport[2];
						int screenHeight = iViewport[1] + iViewport[3];
						int resolutionWidth = GameSystems::GraphicsSystem::Camera::getInstance().resolutionWidth;
						int resolutionHeight = GameSystems::GraphicsSystem::Camera::getInstance().resolutionHeight;

						/*std::cout << "screenWidth: " << screenWidth << "\tscreenHeight: " << screenHeight << std::endl;
						std::cout << "resolutionWidth: " << resolutionWidth << "\tresolutionHeight: " << resolutionHeight << std::endl;*/

						int centerX = (this->getComposition()->getX() + (this->getComposition()->getWidth() / 2)) * screenWidth / resolutionWidth;
						int centerY = (this->getComposition()->getY() + (this->getComposition()->getHeight() / 2)) * screenHeight / resolutionHeight;

						glm::vec2 direction = glm::vec2(event.mouseButton.x - centerX, event.mouseButton.y - centerY);

						GameObjects::BaseGameObject *arrow = GameSystems::ObjectFactory::getInstance().createArrow(getComposition(), getComposition()->getX(),
							getComposition()->getY(), this->getDuration(), glm::normalize(direction));
						this->setDuration(500.0f);
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

	int	KeyboardInputComponent::ParseInputFile(GameTools::JsonValue o) {
		switch (o.getTag()) {
		case GameTools::JSON_OBJECT:
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
