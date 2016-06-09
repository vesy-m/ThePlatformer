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
		if (this->haveToListenMove && event.type == sf::Event::MouseMoved) {
			int mousex = event.mouseMove.x;
			int mousey = event.mouseMove.y;
			this->RelativeCoordToWin(mousex, mousey);
			
			this->composition->sendMessage(new GameMessage::MouseMessageMove(mousex, mousey));
		}
		if (event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
			int mousex = event.mouseWheelScroll.x;
			int mousey = event.mouseWheelScroll.y;
			this->RelativeCoordToWin(mousex, mousey);

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