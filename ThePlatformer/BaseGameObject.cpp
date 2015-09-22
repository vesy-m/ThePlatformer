#include "BaseGameObject.h"

namespace GameObjects {
	BaseGameObject::BaseGameObject()
	{
		this->componentsList = std::vector<BaseComponent*>();
	}

	BaseGameObject::~BaseGameObject()
	{
	}

	std::vector<BaseComponent*> BaseGameObject::getComponents(std::string key)
	{
		return this->componentsList;
	}
}
