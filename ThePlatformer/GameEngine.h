#pragma once
#ifndef __GAMEENGINE_H_
#define __GAMEENGINE_H_

namespace GameEngine {
	class Core {
	public:
		Core();
		virtual ~Core();
		void loop();
	};
}


#endif /* __GAMEENGINE_H_ */