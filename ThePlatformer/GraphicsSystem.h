#pragma once
#ifndef _GRAPHICSSYSTEM_H_
#define _GRAPHICSSYSTEM_H_

#include "BaseSystem.h"
#include "Camera.h"
#include <SFML\OpenGL.hpp>

namespace GameSystems {
	class GraphicsSystem : public BaseSystem
	{
	public:
		GraphicsSystem();
		~GraphicsSystem();
		int Update(double dt, std::list<GameObjects::BaseGameObject*>&);
		void Init(std::list<GameObjects::BaseGameObject*>& listObjects);
		void viewportReload();
		void resizeCamera();
		void SendMessage();
	};
}
#endif // !_GRAPHICSSYSTEM_H_