#pragma once
#ifndef _WINDOWINPUTSYSTEM_H_
#define _WINDOWINPUTSYSTEM_H_

#include "System.h"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

namespace GameSystems {
	class WindowInputSytem : public System
	{
	public:
		WindowInputSytem();
		~WindowInputSytem();
		int Update(float dt, std::list<GameObjects::BaseGameObject*>&);
		void Init(std::list<GameObjects::BaseGameObject*>& listObjects);
		void SendMessage();
	private:
		sf::Window *window;
	};
}
#endif // !_WINDOWINPUTSYSTEM_H_