#include "TimerComponent.h"
#include "Message.h"


namespace GameComponents {
	TimerComponent::TimerComponent(GameObjects::BaseGameObject *object) : BaseComponent(object)
	{
		object->attachComponent(this);
	}

	TimerComponent::~TimerComponent()
	{
	}

	COMPONENT_TYPE TimerComponent::getType() const
	{
		return COMPONENT_TYPE::MECHANIC;
	}

	void TimerComponent::Init()
	{
		this->savedTime = 0;
		this->time = 0;
		this->timing = false;
	}

	void TimerComponent::Update(double dt)
	{
		if (!this->timing) return;

		this->savedTime += dt;

		if (this->savedTime >= this->time) 
		{
			switch (this->timerType)
			{
			case GameObjects::BAT:
				deathTime();
				break;
			case GameObjects::BLOCK:
				invincibleTime();
				break;
			case GameObjects::DASH:
				stopDash();
				break;
			}
			this->timing = false;
		}
	}

	void TimerComponent::sendMessage(GameMessage::Message *message){}

	void TimerComponent::setTimerType(GameObjects::ProjectileType timerType)
	{
		this->timerType = timerType;
	}

	void TimerComponent::setTime(double deathTime)
	{
		this->time = deathTime;
	}

	void TimerComponent::startTimer()
	{
		this->timing = true;
	}

	void TimerComponent::stopTimer()
	{
		this->timing = false;
	}

	void TimerComponent::deathTime()
	{
		this->composition->destroy(true);
	}

	void TimerComponent::invincibleTime()
	{
		this->composition->setInvicible(false);
		this->composition->sendMessage(new GameMessage::Message(GameMessage::STOP_BLOCK));
		this->composition->sendMessage(new GameMessage::Message(GameMessage::ATTACK3_RELEASED));
	}

	void TimerComponent::stopDash()
	{
		this->composition->sendMessage(new GameMessage::Message(GameMessage::STOP_DASH));
		this->composition->setInvicible(false);
	}

}
