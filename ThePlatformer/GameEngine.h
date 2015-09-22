#pragma once
#ifndef __GAMEENGINE_H_
#define __GAMEENGINE_H_

#include <list>
#include "System.h"

namespace GameEngine {
	class Core {
	public:
		Core();
		virtual ~Core();
		void Update(float dt);
		void MainLoop(void);
		void Add(GameSystems::System *sys);
	private:
		std::list<GameSystems::System *> m_systems;
	};
}


#endif /* __GAMEENGINE_H_ */