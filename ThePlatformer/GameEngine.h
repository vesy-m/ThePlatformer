#pragma once
#ifndef __GAMEENGINE_H_
#define __GAMEENGINE_H_

#include <list>
#include "System.h"

#define DT 42

namespace GameEngine {
	class Core {
	public:
		Core();
		virtual ~Core();
		void Init(void);
		void Update(float dt);
		void MainLoop(void);
		void Add(GameObjects::BaseGameObject*);
		void Add(GameSystems::System *sys);
	private:
		std::list<GameObjects::BaseGameObject*> m_objects;
		std::list<GameSystems::System *> m_systems;
	};
}


#endif /* __GAMEENGINE_H_ */