#include "MouseComponent.h"


namespace GameComponents {

	MouseComponent::MouseComponent(GameObjects::BaseGameObject *object, bool listenMove) : InputComponent(object)
	{
		this->haveToListenMove = listenMove;
	}

	MouseComponent::~MouseComponent()
	{
	}

	void MouseComponent::UpdateInputState(sf::Event event, double dt)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->composition->sendMessage(new GameMessage::MouseMessageClick(0, 0, true, false));
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			this->composition->sendMessage(new GameMessage::MouseMessageClick(0, 0, false, true));
		}
		/*
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left || event.mouseButton.button == sf::Mouse::Right)
			{
				bool leftClick = false;
				bool rightClick = false;
				int mousex = event.mouseButton.x;
				int mousey = event.mouseButton.y;
				this->RelativeCoordToWin(mousex, mousey);

				if (event.mouseButton.button == sf::Mouse::Left) {
					std::cout << "left-click " << mousex << " " << mousey << std::endl;
					leftClick = true;
				}
				if (event.mouseButton.button == sf::Mouse::Right) {
					std::cout << "right-click " << mousex << " " << mousey << std::endl;
					rightClick = true;
				}
				this->composition->sendMessage(new GameMessage::MouseMessageClick(mousex, mousey, leftClick, rightClick));
			}
		}*/
		if (this->haveToListenMove && event.type == sf::Event::MouseMoved) {
			int mousex = event.mouseMove.x;
			int mousey = event.mouseMove.y;
			this->RelativeCoordToWin(mousex, mousey);
			
			//std::cout << mousex << " " << mousey << std::endl;
			this->composition->sendMessage(new GameMessage::MouseMessageMove(mousex, mousey));
		}
		if (event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
			int mousex = event.mouseWheelScroll.x;
			int mousey = event.mouseWheelScroll.y;
			this->RelativeCoordToWin(mousex, mousey);

			//std::cout << event.mouseWheelScroll.delta << std::endl;
			this->composition->sendMessage(new GameMessage::MouseMessageWheel(mousex, mousey, (int)event.mouseWheelScroll.delta));
		}
	}

	void MouseComponent::Init()
	{
	}

	void MouseComponent::sendMessage(GameMessage::Message*)
	{
	}

	void MouseComponent::RelativeCoordToWin(int & x, int & y) {
		GLint iViewport[4];
		glGetIntegerv(GL_VIEWPORT, iViewport);
		int screenWidth = iViewport[0] + iViewport[2];
		int screenHeight = iViewport[1] + iViewport[3];
		int resolutionWidth = GameSystems::GraphicsSystem::Camera::getInstance().resolutionWidth;
		int resolutionHeight = GameSystems::GraphicsSystem::Camera::getInstance().resolutionHeight;
		x = x * resolutionWidth / screenWidth;
		y = y * resolutionHeight / screenHeight;
	}

}