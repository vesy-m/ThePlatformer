#pragma once

#include "InputComponent.h"
#include "ObjectFactory.h"
#include <SFML/Window.hpp>

namespace GameComponents {

	class MouseClickComponent : public InputComponent
	{
		friend class GameSystems::ObjectFactory;
	private:
		MouseClickComponent(GameObjects::BaseGameObject *object);
	public:
		virtual ~MouseClickComponent();
		virtual void UpdateInputState(sf::Event, double);
		virtual void Init();
		virtual void sendMessage(GameMessage::Message*);
	};
}