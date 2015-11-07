#pragma once
#include "InputComponent.h"

namespace GameComponents {
	class KeyboardInputComponent : InputComponent
	{
	public:
		KeyboardInputComponent(GameObjects::BaseGameObject *object, std::string filename);
		~KeyboardInputComponent();
		virtual void UpdateInputState(sf::Event, double);
		void Init();
		void sendMessage(GameMessage::Message*);
		int	ParseInputFile(JsonValue o);

	private:
		std::map<INPUT_TYPE, int> keyboardMap;
		std::map<INPUT_TYPE, sf::Mouse::Button> mouseMap;
		std::string filename;
	};
}

