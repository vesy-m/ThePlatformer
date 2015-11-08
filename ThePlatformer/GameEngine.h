#pragma once
#ifndef __GAMEENGINE_H_
#define __GAMEENGINE_H_

#include <list>
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
		void LoadLevelFile(const std::string&);
	private:
		TimeManager								*m_manager;
		std::list<GameSystems::BaseSystem *>		m_systems;
	};
}


#endif /* __GAMEENGINE_H_ */