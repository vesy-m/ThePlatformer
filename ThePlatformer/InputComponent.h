#pragma once
#ifndef _INPUTCOMPONENT_H_
#define _INPUTCOMPONENT_H_

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML\Window.hpp>
#include <map>
#include <sstream>
#include "JSONParser.h"
#include "BaseGameObject.h"
#include "debugManager.h"
#include "ObjectFactory.h"

namespace GameComponents {

	class InputComponent : BaseComponent
	{	
	public:
		enum INPUT_TYPE
		{
			LEFT = 0,
			RIGHT = 1,
			JUMP = 2,
			FIRE = 3,
			SPECIAL = 4,
			DEBUG = 5,
			ROTATE_RIGHT = 6,
			ROTATE_LEFT = 7,
		};
		InputComponent(GameObjects::BaseGameObject *);
		~InputComponent();

		COMPONENT_TYPE getType();
		GameObjects::BaseGameObject *getComposition();
		void Update(double);

		virtual void UpdateInputState(sf::Event) = 0;
		virtual void Init() = 0;
		virtual void sendMessage(Message*) = 0;

	protected:
		const COMPONENT_TYPE componentType = WINDOW;
		std::map<INPUT_TYPE, bool> inputState;
	};
}

#endif // !_INPUTCOMPONENT_H_

