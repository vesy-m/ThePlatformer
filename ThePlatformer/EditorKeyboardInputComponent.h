#pragma once
#include "InputComponent.h"

namespace GameSystems {
	class ObjectFactory;
}

namespace GameComponents {
	class EditorKeyboardInputComponent : public InputComponent
	{
		friend class GameSystems::ObjectFactory;
		friend class GameTools::EditorManager;
	private:
		EditorKeyboardInputComponent(GameObjects::BaseGameObject*, bool);
	public:
		virtual ~EditorKeyboardInputComponent();
		virtual void UpdateInputState(sf::Event, double);
		virtual void Init();
		virtual void sendMessage(GameMessage::Message*);
		COMPONENT_TYPE getType() { return EDITOR_KEYBOARD; }
	private:
		int saveX;
		bool saveRight;
	};
}

