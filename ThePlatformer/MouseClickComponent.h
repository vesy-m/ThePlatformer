#pragma once

#include "InputComponent.h"
#include "ObjectFactory.h"
#include <SFML/Window.hpp>
#include "MenuControllerMessage.h"

namespace GameComponents {

	class MouseClickComponent : public InputComponent
	{
		friend class GameSystems::ObjectFactory;
	private:
		MouseClickComponent(GameObjects::BaseGameObject * object, int listeningMode = 0);
		bool checkPressAOrEnter(sf::Event event);
		int listeningMode;
	public:
		virtual ~MouseClickComponent();
		virtual void UpdateInputState(sf::Event, double);
		virtual void Init();
		virtual void sendMessage(GameMessage::Message*);
		int idPadSelected;
		void OneKeyPressInMenu(sf::Event event);
		std::vector<int> listPadAlreadySelected;
	};
}