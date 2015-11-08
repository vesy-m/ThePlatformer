#pragma once
#ifndef _WINDOWINPUTSYSTEM_H_
#define _WINDOWINPUTSYSTEM_H_

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
		void Init(std::list<GameObjects::BaseGameObject*>& listObjects);
		void SendMessage();
	private:
		sf::Window *window;
		bool fullscreen;
	};
}
#endif // !_WINDOWINPUTSYSTEM_H_