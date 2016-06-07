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
			case GameObjects::TENNIS_BALL1:
			case GameObjects::TENNIS_BALL2:
			case GameObjects::BASE_BALL:
			case GameObjects::RUGBY_BALL:
			case GameObjects::DROP:
			case GameObjects::BAT:
			case GameObjects::TENNIS_BREAK:
			case GameObjects::PUNCH:
			case GameObjects::SPECIAL_PUNCH:
			case GameObjects::BOXER_POWERUP_AURA:
				deathTime();
				break;
			case GameObjects::BLOCK:
				blockInvincibleTime();
				break;
			case GameObjects::DASH:
				stopDash();
				break;
			case GameObjects::DASH_DAMAGE:
				stopDash();
				break;
			case GameObjects::BOXER_POWERUP:
				stopPowerup();
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

	void TimerComponent::blockInvincibleTime()
	{
		this->composition->setInvicible(false);
		this->composition->sendMessage(new GameMessage::Message(GameMessage::STOP_BLOCK));
		this->composition->sendMessage(new GameMessage::Message(GameMessage::ATTACK3_RELEASED));
	}

	void TimerComponent::dashDamageTimeBehaviour()
	{
		this->composition->setInvicible(false);
	}

	void TimerComponent::stopDash()
	{
		this->composition->sendMessage(new GameMessage::Message(GameMessage::STOP_DASH));
		this->composition->setInvicible(false);
	}

	void TimerComponent::stopPowerup()
	{
		this->composition->setPowerupDamage(1);
		this->composition->setPowerupDefense(1);
	}

}
