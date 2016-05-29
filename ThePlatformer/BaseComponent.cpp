#include "BaseComponent.h"

namespace GameComponents {
	BaseComponent::BaseComponent(GameObjects::BaseGameObject * object)
	{
		this->composition = object;
		this->isActive = true;
	}

	BaseComponent::~BaseComponent()
	{
	}

	void BaseComponent::SetActive(bool state)
	{
		this->isActive = state;
	}

	bool BaseComponent::IsComponentActive()
	{
		return this->isActive;
	}

	GameObjects::BaseGameObject *BaseComponent::getComposition(void) const {
		return this->composition;
	}
}