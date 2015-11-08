#pragma once
#ifndef __GAMEENGINE_H_
#define __GAMEENGINE_H_

#include <list>
#include "System.h"
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
		void Add(GameSystems::System*);
	private:
		TimeManager								*m_manager;
		
	};
}


#endif /* __GAMEENGINE_H_ */