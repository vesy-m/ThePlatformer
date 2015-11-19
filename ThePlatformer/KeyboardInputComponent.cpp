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
						if (this->savedDt < this->maxElapsedTime) break;
						GLint iViewport[4];
						glGetIntegerv(GL_VIEWPORT, iViewport);
						int screenWidth = iViewport[0] + iViewport[2];
						int screenHeight = iViewport[1] + iViewport[3];
						int resolutionWidth = GameSystems::GraphicsSystem::Camera::getInstance().resolutionWidth;
						int resolutionHeight = GameSystems::GraphicsSystem::Camera::getInstance().resolutionHeight;

						int cameraWith = GameSystems::GraphicsSystem::Camera::getInstance().cameraEndX - GameSystems::GraphicsSystem::Camera::getInstance().cameraStartX;
						int cameraHeight = GameSystems::GraphicsSystem::Camera::getInstance().cameraEndY - GameSystems::GraphicsSystem::Camera::getInstance().cameraStartY;
						int mouseX = event.mouseButton.x * cameraWith / screenWidth;
						int mouseY = event.mouseButton.y * cameraHeight / screenHeight;

						mouseX += GameSystems::GraphicsSystem::Camera::getInstance().cameraStartX;
						mouseY += GameSystems::GraphicsSystem::Camera::getInstance().cameraStartY;

						int centerX = (this->getComposition()->getX() + (this->getComposition()->getWidth() / 2));
						int centerY = (this->getComposition()->getY() + (this->getComposition()->getHeight() / 2));

						glm::vec2 direction = glm::vec2(mouseX - centerX, mouseY - centerY);

						GameObjects::BaseGameObject *arrow = GameSystems::ObjectFactory::getInstance().createArrow(getComposition(), getComposition()->getX(),
						getComposition()->getY(), this->getDuration(), glm::normalize(direction));
						this->setDuration(500.0f);
						this->savedDt = 0.0f;
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
		case GameMessage::JUMP_RELEASED:
			inputState.at(INPUT_TYPE::JUMP) = false;
			break;
		default:
			break;
		}
	}
}
