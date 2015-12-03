#include "MouseClickComponent.h"


namespace GameComponents {

	MouseClickComponent::MouseClickComponent(GameObjects::BaseGameObject *object, int listeningMode) : InputComponent(object)
	{
		this->idPadSelected = -1;
		/* listening mode:
		0 : listen all
		1 : listen just one first press a or enter
		*/
		this->listeningMode = listeningMode;
	}

	bool MouseClickComponent::checkPressAOrEnter(sf::Event event)
	{
		if (event.type == sf::Event::JoystickButtonReleased && event.joystickButton.button == 0 && GameSystems::ObjectFactory::getInstance().controllerAlreadyTook(event.joystickButton.joystickId) == false) {
			this->idPadSelected = event.joystickButton.joystickId;
			return true;
		} else if (event.type == sf::Event::KeyReleased && event.key.code == 58 && GameSystems::ObjectFactory::getInstance().controllerAlreadyTook(8) == false) {
			this->idPadSelected = 8;
			return true;
		}
		return false;
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
				//std::cout << mousex << " " << mousey << std::endl;


				if (this->composition->getX() < mousex && mousex < this->composition->getX() + this->composition->getWidth() &&
					this->composition->getY() < mousey && mousey < this->composition->getY() + this->composition->getHeight()) {
					this->composition->sendMessage(new GameMessage::Message(GameMessage::CLICKON));
				}
			}
		}
		if (event.type == sf::Event::MouseMoved) {
			GLint iViewport[4];
			glGetIntegerv(GL_VIEWPORT, iViewport);
			int screenWidth = iViewport[0] + iViewport[2];
			int screenHeight = iViewport[1] + iViewport[3];
			int resolutionWidth = GameSystems::GraphicsSystem::Camera::getInstance().resolutionWidth;
			int resolutionHeight = GameSystems::GraphicsSystem::Camera::getInstance().resolutionHeight;
			int mousex = event.mouseMove.x * resolutionWidth / screenWidth;
			int mousey = event.mouseMove.y * resolutionHeight / screenHeight;
			//std::cout << mousex << " " << mousey << std::endl;


			if (this->composition->getX() < mousex && mousex < this->composition->getX() + this->composition->getWidth() &&
				this->composition->getY() < mousey && mousey < this->composition->getY() + this->composition->getHeight()) {
				GameSystems::ObjectFactory::getInstance().changeSelectedButtonMenu(this->composition);
			}
		}
		if (this->listeningMode == 1) {
			if (this->idPadSelected == -1) {
				// while no pad selected
				if (checkPressAOrEnter(event)) {
					//std::cout << "a or enter pressed : " << this->idPadSelected << " take" << std::endl;
					this->composition->sendMessage(new GameMessage::MenuControllerMessage(GameMessage::SELECT_CONTROLLER_MENU, this->idPadSelected));
				}
			}
			else {
				// after pad selection
				if (// if pad move or release
					((event.type == sf::Event::JoystickButtonReleased || event.type == sf::Event::JoystickMoved) && event.joystickButton.joystickId == this->idPadSelected) ||
					// or if keyboard release
					(event.type == sf::Event::KeyReleased && this->idPadSelected == 8)) 
				{
					//std::cout << this->idPadSelected << " presse or moved" << std::endl;
					OneKeyPressInMenu(event);
				}
			}
		}
		else {
			OneKeyPressInMenu(event);
		}
	}

	void MouseClickComponent::OneKeyPressInMenu(sf::Event event) {
		GameMessage::MessageId idMessage = GameMessage::DEFAULT;
		if (event.type == sf::Event::JoystickButtonReleased) {
			if (event.joystickButton.button == 0) { idMessage = GameMessage::ENTERMENU;	}
			else if (event.joystickButton.button == 7) { idMessage = GameMessage::START_MENU; }
			else if (event.joystickButton.button == 1) { idMessage = GameMessage::B_MENU; }
		} else if (event.type == sf::Event::JoystickMoved) {
			if (event.joystickMove.axis == 6 || event.joystickMove.axis == 0 || event.joystickMove.axis == 4)
			{
				if (event.joystickMove.position == -100) { idMessage = GameMessage::LEFTMENU; }
				else if (event.joystickMove.position == 100) { idMessage = GameMessage::RIGHTMENU; }
			}
			else if (event.joystickMove.axis == 7 || event.joystickMove.axis == 1 || event.joystickMove.axis == 3)
			{
				int multiplicator = 1;
				if (event.joystickMove.axis == 1 || event.joystickMove.axis == 3) multiplicator = -1;
				if (event.joystickMove.position == 100 * multiplicator) { idMessage = GameMessage::UPMENU; }
				else if (event.joystickMove.position == -100 * multiplicator) { idMessage = GameMessage::DOWNMENU; }
			}
		} else if (event.type == sf::Event::KeyReleased){
			if (event.key.code == sf::Keyboard::Return) { idMessage = GameMessage::ENTERMENU; } 
			else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) { idMessage = GameMessage::LEFTMENU; }
			else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) { idMessage = GameMessage::RIGHTMENU; }
			else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) { idMessage = GameMessage::UPMENU; }
			else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) { idMessage = GameMessage::DOWNMENU; }
			else if (event.key.code == sf::Keyboard::Escape) { idMessage = GameMessage::ECHAP_MENU; }
		}
		if (idMessage != GameMessage::DEFAULT) {
			//std::cout << "key press send message : " << idMessage << std::endl;
			this->composition->sendMessage(new GameMessage::MenuControllerMessage(idMessage, this->idPadSelected));
		}
	}

	void MouseClickComponent::Init()
	{
	}

	void MouseClickComponent::sendMessage(GameMessage::Message*)
	{
	}

}