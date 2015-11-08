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
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (this->composition->getX() < event.mouseButton.x && event.mouseButton.x < this->composition->getX() + this->composition->getWidth() &&
					this->composition->getY() < event.mouseButton.y && event.mouseButton.y < this->composition->getY() + this->composition->getHeight()) {
					this->composition->sendMessage(new GameMessage::Message(GameMessage::Message::CLICKON));
				}
			}
		}
	}

	void MouseClickComponent::Init()
	{
	}

	void MouseClickComponent::sendMessage(GameMessage::Message *)
	{
	}

}