#pragma once
#ifndef __GAMEOBJECT_H_
#define __GAMEOBJECT_H_

namespace GameEngine {
	class GameObject {
	public:
		GameObject();
		virtual ~GameObject();
		virtual void display() const = 0;
		virtual void move(unsigned int, unsigned int) = 0;
	private:
		unsigned int _pos_x;
		unsigned int _pos_y;
	};
}

#endif /* __GAMEOBJECT_H_ */