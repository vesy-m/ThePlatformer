#include "BodyComponent.h"


namespace GameComponents {

	BodyComponent::BodyComponent(GameObjects::BaseGameObject * composition)
	{
	}

	BodyComponent::~BodyComponent()
	{
	}

	COMPONENT_TYPE BodyComponent::getType()
	{
		return COMPONENT_TYPE::PHYSIC;
	}

	void BodyComponent::Update()
	{

	}

	void BodyComponent::Init()
	{
	}
}