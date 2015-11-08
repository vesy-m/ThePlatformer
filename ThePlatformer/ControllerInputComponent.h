#pragma once
#include "InputComponent.h"

namespace GameSystems {
	class ObjectFactory;
}

namespace GameComponents {

	class ControllerInputComponent : public InputComponent
	{
		friend class GameSystems::ObjectFactory;
	private:
		ControllerInputComponent(GameObjects::BaseGameObject*, std::string);
	public:
		
		virtual ~ControllerInputComponent();

		virtual void UpdateInputState(sf::Event, double);
		virtual void Init();
		virtual void sendMessage(GameMessage::Message*);
		bool ControllerInputComponent::DetectAxisInput(sf::Event event, int button);
		bool ControllerInputComponent::CheckInputValue(sf::Event event, int button);
		int	ControllerInputComponent::ParseInputFile(JsonValue o);
	private:
		std::map<INPUT_TYPE, int> controllerMap;
		std::string filename;
	};
}

