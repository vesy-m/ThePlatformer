#pragma once
#include "InputComponent.h"

namespace GameComponents {

	class JoystickInputComponent : InputComponent
	{
		friend class GameSystems::ObjectFactory;
	private:
		JoystickInputComponent(GameObjects::BaseGameObject *object);
	public:
		
		~JoystickInputComponent();

		void UpdateInputState(sf::Event);
		void Init();
		void sendMessage(Message*);
		bool JoystickInputComponent::DetectAxisInput(sf::Event event, int button);
		bool JoystickInputComponent::CheckInputValue(sf::Event event, int button);

	private:
		std::map<INPUT_TYPE, int> joystickMap;
		std::map<INPUT_TYPE, sf::Mouse::Button> mouseMap;
	};
}

