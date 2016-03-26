#include "DeathTimerComponent.h"


namespace GameComponents {
	DeathTimerComponent::DeathTimerComponent(GameObjects::BaseGameObject *object) : BaseComponent(object)
	{
		object->attachComponent(this);
	}

	DeathTimerComponent::~DeathTimerComponent()
	{
	}

	COMPONENT_TYPE DeathTimerComponent::getType() const
	{
		return COMPONENT_TYPE::MECHANIC;
	}

	void DeathTimerComponent::Init()
	{
		this->savedTime = 0;
		this->deathTime = 0;
	}

	void DeathTimerComponent::Update(double dt)
	{
		this->savedTime += dt;

		if (this->savedTime >= this->deathTime) this->composition->destroy();
	}


	void DeathTimerComponent::sendMessage(GameMessage::Message *message)
	{
	}

	void DeathTimerComponent::setDeathTime(double deathTime)
	{
		this->deathTime = deathTime;
	}
}
