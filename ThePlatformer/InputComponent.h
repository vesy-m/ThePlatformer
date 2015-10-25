#pragma once
#ifndef _INPUTCOMPONENT_H_
#define _INPUTCOMPONENT_H_

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML\Window.hpp>
#include <map>
#include "BaseGameObject.h"
#include "debugManager.h"
#include "ObjectFactory.h"

namespace GameComponents {

	class InputComponent : BaseComponent
	{	
	public:
		enum INPUT_TYPE
		{
			LEFT,
			RIGHT,
			JUMP,
			FIRE,
			SPECIAL,
			DEBUG,
			ROTATE_RIGHT,
			ROTATE_LEFT,
		};
		InputComponent(GameObjects::BaseGameObject *);
		~InputComponent();

		COMPONENT_TYPE getType();
		GameObjects::BaseGameObject *getComposition();
		void Update();

		virtual void UpdateInputState(sf::Event) = 0;
		virtual void Init() = 0;
		virtual void sendMessage(Message*) = 0;

	protected:
		const COMPONENT_TYPE componentType = WINDOW;
		std::map<INPUT_TYPE, bool> inputState;
	};
}

#endif // !_INPUTCOMPONENT_H_

