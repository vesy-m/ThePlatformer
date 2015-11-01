#pragma once
#include "InputComponent.h"

namespace GameComponents {

	class ControllerInputComponent : InputComponent
	{
	public:
		ControllerInputComponent(GameObjects::BaseGameObject *object, std::string filename);
		~ControllerInputComponent();

		void UpdateInputState(sf::Event);
		void Init();
		void sendMessage(Message*);
		bool ControllerInputComponent::DetectAxisInput(sf::Event event, int button);
		bool ControllerInputComponent::CheckInputValue(sf::Event event, int button);
		int	ControllerInputComponent::ParseInputFile(JsonValue o);

	private:
		std::map<INPUT_TYPE, int> controllerMap;
		std::string filename;
	};
}

