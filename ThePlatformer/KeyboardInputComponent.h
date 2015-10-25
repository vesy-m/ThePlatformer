#pragma once
#include "InputComponent.h"

namespace GameComponents {
	class KeyboardInputComponent : InputComponent
	{
		friend class GameSystems::ObjectFactory;
	private:
		KeyboardInputComponent(GameObjects::BaseGameObject*);
	public:
		
		~KeyboardInputComponent();
		void UpdateInputState(sf::Event);
		void Init();
		void sendMessage(Message*);

	private:
		std::map<INPUT_TYPE, sf::Keyboard::Key> keyboardMap;
		std::map<INPUT_TYPE, sf::Mouse::Button> mouseMap;
	};
}

