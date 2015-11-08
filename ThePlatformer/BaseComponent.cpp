#include "BaseComponent.h"

namespace GameComponents {
	BaseComponent::BaseComponent(GameObjects::BaseGameObject * object)
	{
		this->composition = object;
		object->attachComponent(this);
	}

	BaseComponent::~BaseComponent()
	{
	}
}