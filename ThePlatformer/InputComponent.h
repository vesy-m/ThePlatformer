#pragma once
#ifndef _INPUTCOMPONENT_H_
#define _INPUTCOMPONENT_H_

#include <SFML/Window/Keyboard.hpp>
#include <map>
#include "BaseGameObject.h"

namespace GameComponents {

	enum INPUT_TYPE
	{
		LEFT,
		RIGHT,
		JUMP
	};

	class InputComponent : BaseComponent
	{
	public:
		InputComponent(COMPONENT_TYPE componentType);
		~InputComponent();

		COMPONENT_TYPE getType();
		void Update();
		void Init();

	private:
		COMPONENT_TYPE componentType;
		std::map<INPUT_TYPE, sf::Keyboard::Key> inputMap;
	};
}

#endif // !_INPUTCOMPONENT_H_

