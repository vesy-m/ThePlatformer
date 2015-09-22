#include "BaseGameObject.h"

namespace GameObjects {
	BaseGameObject::BaseGameObject()
	{
		this->componentsList = std::vector<GameComponents::BaseComponent*>();
	}

	BaseGameObject::~BaseGameObject()
	{
	}

	std::vector<GameComponents::BaseComponent*> BaseGameObject::getComponents(GameComponents::COMPONENT_TYPE type)
	{
		// a changer
		std::vector<GameComponents::BaseComponent*> newVect = std::vector<GameComponents::BaseComponent*>();
		for (size_t i = 0; i < this->componentsList.size(); i++)
		{
			GameComponents::BaseComponent* elem = this->componentsList.at(i);
			if (elem->getType() == GameComponents::COMPONENT_TYPE::WINDOW) {
				newVect.push_back(elem);
			}
		}
		return newVect;
	}
	void BaseGameObject::attachComponent(GameComponents::BaseComponent *component)
	{
		this->componentsList.push_back(component);
	}
}
