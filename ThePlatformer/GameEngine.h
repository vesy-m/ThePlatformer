#pragma once
#ifndef __GAMEENGINE_H_
#define __GAMEENGINE_H_
#include <list>
#include "GameObject.h"

namespace GameEngine {
	class Core {
	public:
		Core();
		virtual ~Core();
		void loop();
		void registerObject(GameObject*);
		void destroyObject(GameObject*);
	private:
		std::list<GameObject*> _objectList;
	};
}


#endif /* __GAMEENGINE_H_ */