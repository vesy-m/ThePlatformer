#pragma once
#include "InputComponent.h"

namespace GameSystems {
	class ObjectFactory;
}

namespace GameComponents {
	class KeyboardInputComponent : public InputComponent
	{
		friend class GameSystems::ObjectFactory;
	private:
		KeyboardInputComponent(GameObjects::BaseGameObject*, std::string);
	public:
		virtual ~KeyboardInputComponent();
		virtual void UpdateInputState(sf::Event, double);
		virtual void Init();
		virtual void sendMessage(GameMessage::Message*);
		int	ParseInputFile(GameTools::JsonValue);
		//void setMousePosition(sf::Event);
	private:
		std::map<INPUT_TYPE, int> keyboardMap;
		std::string inputFilename;
	};
}

