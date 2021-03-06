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
		if (this->listeningMode == 1) {
			if (this->idPadSelected == -1) {
				// while no pad selected
				if (checkPressAOrEnter(event))
					this->composition->sendMessage(new GameMessage::MenuControllerMessage(GameMessage::SELECT_CONTROLLER_MENU, this->idPadSelected));
			}
			else {
				// after pad selection
				if (// if pad move or release
					((event.type == sf::Event::JoystickButtonReleased || event.type == sf::Event::JoystickMoved) && event.joystickButton.joystickId == this->idPadSelected) ||
					// or if keyboard release
					(event.type == sf::Event::KeyReleased && this->idPadSelected == 8)) 
				{
					OneKeyPressInMenu(event);
				}
			}
		}
		else
			OneKeyPressInMenu(event);
	}

	void MouseClickComponent::OneKeyPressInMenu(sf::Event event) {
		GameMessage::MessageId idMessage = GameMessage::DEFAULT;
		if (event.type == sf::Event::JoystickButtonReleased) {
			if (event.joystickButton.button == 0) { idMessage = GameMessage::ENTERMENU;	}
			else if (event.joystickButton.button == 7) { idMessage = GameMessage::START_MENU; }
			else if (event.joystickButton.button == 1) { idMessage = GameMessage::B_MENU; }
		} else if (event.type == sf::Event::JoystickMoved) {
			if (event.joystickMove.axis == 5 || event.joystickMove.axis == 0 || event.joystickMove.axis == 6)
			{
				if (event.joystickMove.position == -100) { idMessage = GameMessage::LEFTMENU; }
				else if (event.joystickMove.position == 100) { idMessage = GameMessage::RIGHTMENU; }
			}
			else if (event.joystickMove.axis == 4 || event.joystickMove.axis == 1 || event.joystickMove.axis == 7)
			{
				//dpad up down is inverted
				int multiplicator = 1;
				if (event.joystickMove.axis == 7) multiplicator = -1;
				if (event.joystickMove.position == -100 * multiplicator) { idMessage = GameMessage::UPMENU; }
				else if (event.joystickMove.position == 100 * multiplicator) { idMessage = GameMessage::DOWNMENU; }
			}
		} else if (event.type == sf::Event::KeyReleased){
			if (event.key.code == sf::Keyboard::Return) { idMessage = GameMessage::ENTERMENU; } 
			else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) { idMessage = GameMessage::LEFTMENU; }
			else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) { idMessage = GameMessage::RIGHTMENU; }
			else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) { idMessage = GameMessage::UPMENU; }
			else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) { idMessage = GameMessage::DOWNMENU; }
			else if (event.key.code == sf::Keyboard::Escape) { idMessage = GameMessage::ECHAP_MENU; }
		}
		if (idMessage != GameMessage::DEFAULT)
			this->composition->sendMessage(new GameMessage::MenuControllerMessage(idMessage, this->idPadSelected));
	}

	void MouseClickComponent::Init()
	{
	}

	void MouseClickComponent::sendMessage(GameMessage::Message*)
	{
	}
}