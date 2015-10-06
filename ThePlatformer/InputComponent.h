#pragma once
#ifndef _INPUTCOMPONENT_H_
#define _INPUTCOMPONENT_H_

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML\Window.hpp>
#include <map>
#include "BaseGameObject.h"

namespace GameComponents {

	enum INPUT_TYPE
	{
		LEFT,
		RIGHT,
		JUMP,
		FIRE,
		SPECIAL,
		DEBUG
	};

	class InputComponent : BaseComponent
	{
	public:
		InputComponent(GameObjects::BaseGameObject *);
		~InputComponent();

		COMPONENT_TYPE getType();
		void Update();
		void UpdateInputState(sf::Event);
		void Init();
		void sendMessage(Message*);
		void setKeyboardKey(INPUT_TYPE inputType, sf::Keyboard::Key key);
		void setMouseButton(INPUT_TYPE inputType, sf::Mouse::Button button);

	private:
		const COMPONENT_TYPE componentType = WINDOW;
		std::map<INPUT_TYPE, bool> inputState;
		std::map<INPUT_TYPE, sf::Keyboard::Key> keyboardMap;
		std::map<INPUT_TYPE, sf::Mouse::Button> mouseMap;
	};
}

#endif // !_INPUTCOMPONENT_H_

