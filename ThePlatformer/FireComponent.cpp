#include "FireComponent.h"

namespace GameComponents {
	FireComponent::FireComponent(GameObjects::BaseGameObject *object) : BaseComponent(object) {
		object->attachComponent(this);
	}

	FireComponent::~FireComponent() {

	}
}