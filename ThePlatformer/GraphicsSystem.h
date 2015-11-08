#pragma once
#ifndef _GRAPHICSSYSTEM_H_
#define _GRAPHICSSYSTEM_H_

#include "BaseSystem.h"
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
		class Camera;		
	};

	class GraphicsSystem::Camera
	{
	public:
		~Camera();
		static Camera& getInstance()
		{
			static Camera    instance;
			return instance;
		}
		int cameraStartX;
		int cameraStartY;
		int cameraEndY;
		int cameraEndX;
		void setX(int x);
		void setY(int y);
		void setWidth(int width);
		void setHeight(int height);
		int resolutionWidth;
		int resolutionHeight;
		void setResolution720p();
		void setResolution1080p();
	private:
		Camera();
		Camera(Camera const&) = delete;
		void operator=(Camera const&) = delete;
	};
}
#endif // !_GRAPHICSSYSTEM_H_