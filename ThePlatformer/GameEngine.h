#pragma once
#include <list>
#include <vector>
#include "Texture.h"
#include "BaseSystem.h"
#include "TimeManager.h"

#define FRAME_PER_SECOND 60
namespace GameEngine {
	class Core {
	public:
		Core();
		virtual ~Core();
		void Init(void);
		void Update(float);
		void MainLoop(void);
		void Add(GameSystems::BaseSystem*);
		class Level;
		static bool gameLoop;
	private:
		TimeManager								*m_manager;
		
	};

	class Core::Level
	{
	public:
		Level();
		~Level();
		void putObjectDepthOrdered(GameObjects::BaseGameObject * obj);
		std::list<GameObjects::BaseGameObject*>& getObjects();
		std::vector<GameObjects::BaseGameObject*> getPlayers();
	private:
		GameTools::Texture *background;
		std::list<GameObjects::BaseGameObject *> listGameObject;
		int x;
		int y;
		float scale;
	};

}