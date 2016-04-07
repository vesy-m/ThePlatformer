#pragma once

#include "InputComponent.h"
#include "ObjectFactory.h"
#include "EditorManager.h"
#include <SFML/Window.hpp>
#include "MenuControllerMessage.h"
#include "MouseMessageMove.h"
#include "MouseMessageClick.h"
#include "MouseMessageWheel.h"

namespace GameComponents {

	class MouseComponent : public InputComponent
	{
		friend class GameSystems::ObjectFactory;
		friend class GameTools::EditorManager;
	private:
		MouseComponent(GameObjects::BaseGameObject * object, bool listenMove = false);
		void RelativeCoordToWin(int & x, int & y);

	public:
		virtual ~MouseComponent();
		virtual void UpdateInputState(sf::Event, double);
		virtual void Init();
		virtual void sendMessage(GameMessage::Message*);

		bool haveToListenMove;
	};
}