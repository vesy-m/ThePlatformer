#include <iostream>
#include "GameEngine.h"

namespace GameEngine {
	Core::Core() {

	}

	Core::~Core() {

	}
	
	void Core::loop() {
		while (1) {
		}
	}

	void Core::registerObject(GameObject *obj) {
		this->_objectList.push_back(obj);
	}

	void Core::destroyObject(GameObject *obj) {
		auto it = this->_objectList.begin();
		for (it = it; it != this->_objectList.end(); ++it) {
			if (*it == obj) {
				this->_objectList.erase(it);
				return;
			}
		}
	}
}