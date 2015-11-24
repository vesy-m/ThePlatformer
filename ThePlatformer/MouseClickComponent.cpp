#include "MouseClickComponent.h"


namespace GameComponents {

	MouseClickComponent::MouseClickComponent(GameObjects::BaseGameObject *object) : InputComponent(object)
	{
	}


	MouseClickComponent::~MouseClickComponent()
	{
	}

	void MouseClickComponent::UpdateInputState(sf::Event event, double dt)
	{
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				GLint iViewport[4];
				glGetIntegerv(GL_VIEWPORT, iViewport);
				int screenWidth = iViewport[0] + iViewport[2];
				int screenHeight = iViewport[1] + iViewport[3];
				int resolutionWidth = GameSystems::GraphicsSystem::Camera::getInstance().resolutionWidth;
				int resolutionHeight = GameSystems::GraphicsSystem::Camera::getInstance().resolutionHeight;
				int mousex = event.mouseButton.x * resolutionWidth / screenWidth;
				int mousey = event.mouseButton.y * resolutionHeight / screenHeight;
				std::cout << mousex << " " << mousey << std::endl;


				if (this->composition->getX() < mousex && mousex < this->composition->getX() + this->composition->getWidth() &&
					this->composition->getY() < mousey && mousey < this->composition->getY() + this->composition->getHeight()) {
					this->composition->sendMessage(new GameMessage::Message(GameMessage::CLICKON));
				}
			}
		}
	}

	void MouseClickComponent::Init()
	{
	}

	void MouseClickComponent::sendMessage(GameMessage::Message*)
	{
	}

}