#pragma once
#include "InputComponent.h"

namespace GameComponents {
	class KeyboardInputComponent : InputComponent
	{
	public:
		KeyboardInputComponent(GameObjects::BaseGameObject *object, std::string filename);
		~KeyboardInputComponent();
		void UpdateInputState(sf::Event);
		void Init();
		void sendMessage(Message*);
		int	ParseInputFile(JsonValue o);

	private:
		std::map<INPUT_TYPE, int> keyboardMap;
		std::map<INPUT_TYPE, sf::Mouse::Button> mouseMap;
		std::string filename;
	};
}

