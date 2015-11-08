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
		bool ControllerInputComponent::DetectAxisInput(sf::Event event, int);
		bool ControllerInputComponent::CheckInputValue(sf::Event event, int);
		int	ControllerInputComponent::ParseInputFile(GameTools::JsonValue);
	private:
		std::map<INPUT_TYPE, int> controllerMap;
		std::string filename;
		int controllerNumber;
		float aimAxisX;
		float aimAxisY;
	};
}

