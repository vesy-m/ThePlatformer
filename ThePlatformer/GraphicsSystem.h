#pragma once

#include "BaseSystem.h"
#include <SFML\OpenGL.hpp>
#include "Singleton.h"
#define GL_CLAMP_TO_EDGE 0x812F

namespace GameSystems {
	class GraphicsSystem : public BaseSystem
	{
	public:
		GraphicsSystem();
		~GraphicsSystem();
		int Update(double, std::list<GameObjects::BaseGameObject*>&);
		void Init(std::list<GameObjects::BaseGameObject*>&);
		void viewportReload();
		void resizeCamera();
		void SendAMessage();
		class Camera;
	private:
		GameObjects::BaseGameObject *backgroundObj;
	};

	class GraphicsSystem::Camera : public CSingletonStaticAlloc<GraphicsSystem::Camera>
	{
		friend class CSingletonStaticAlloc<GraphicsSystem::Camera>;
	public:
		~Camera();
		int cameraStartX;
		int cameraStartY;
		int cameraEndY;
		int cameraEndX;
		void setX(int x);
		void setY(int y);
		void setWidth(int);
		void setHeight(int);
		int resolutionWidth;
		int resolutionHeight;
		void setResolution720p();
		void setResolution1080p();
		void reInit();
	private:
		Camera();
		Camera(Camera const&) = delete;
		void operator=(Camera const&) = delete;
	};
}
