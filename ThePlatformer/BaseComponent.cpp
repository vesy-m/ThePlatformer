#include "BaseComponent.h"


namespace GameComponents {


	BaseComponent::BaseComponent(GameObjects::BaseGameObject * object)
	{
		this->composition = object;
	}

	BaseComponent::~BaseComponent()
	{
	}
}