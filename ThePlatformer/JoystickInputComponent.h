#pragma once
#include "InputComponent.h"

namespace GameComponents {

	class JoystickInputComponent : InputComponent
	{
	public:
		JoystickInputComponent(GameObjects::BaseGameObject *object, std::string filename);
		~JoystickInputComponent();

		void UpdateInputState(sf::Event);
		void Init();
		void sendMessage(Message*);
		bool JoystickInputComponent::DetectAxisInput(sf::Event event, int button);
		bool JoystickInputComponent::CheckInputValue(sf::Event event, int button);
		int	JoystickInputComponent::ParseInputFile(JsonValue o);

	private:
		std::map<INPUT_TYPE, int> joystickMap;
		std::string filename;
	};
}

