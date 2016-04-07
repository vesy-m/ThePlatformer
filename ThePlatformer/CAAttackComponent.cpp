#include "CAAttackComponent.h"

namespace GameComponents
{
	CAAttackComponent::CAAttackComponent(GameObjects::BaseGameObject *object) : BaseComponent(object)
	{
		object->attachComponent(this);
	}

	CAAttackComponent::~CAAttackComponent() {}

	void				CAAttackComponent::Update(double) {}

	COMPONENT_TYPE		CAAttackComponent::getType() const { return FIRE; }
}
