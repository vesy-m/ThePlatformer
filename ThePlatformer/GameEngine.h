#pragma once
#ifndef __GAMEENGINE_H_
#define __GAMEENGINE_H_

#include <vector>
#include "System.h"

namespace GameEngine {
	class Core {
	public:
		Core();
		virtual ~Core();
		void Update(float dt);
		void MainLoop(void);
		void Add(System *sys);
	private:
		std::vector<System *> m_systems;
	};
}


#endif /* __GAMEENGINE_H_ */