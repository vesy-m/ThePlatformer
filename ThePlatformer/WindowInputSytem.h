#pragma once

#include "BaseSystem.h"
#include "InputComponent.h"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

namespace GameSystems {
	class WindowInputSytem : public BaseSystem
	{
	public:
		WindowInputSytem();
		~WindowInputSytem();
		int Update(double dt, std::list<GameObjects::BaseGameObject*>&);
		void Init(std::list<GameObjects::BaseGameObject*>&);
		void SendAMessage();
		void switchFullScreen();
		static bool fullscreen;
	private:
		sf::Window *window;
		bool currentFullScreenState;
	};
}