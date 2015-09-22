#pragma once

#include "BaseGameObject.h"
#include <SFML/Window.hpp>

namespace GameComponents {

	class WindowsComponent : BaseComponent
	{
	public:
		WindowsComponent();
		~WindowsComponent();
		COMPONENT_TYPE getType();
		void Update();
		void Init();
	private:
		const COMPONENT_TYPE type = COMPONENT_TYPE::WINDOW;
		sf::Window *window;
	};
}
