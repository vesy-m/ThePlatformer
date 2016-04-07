#pragma once

#include "BaseGameObject.h"

namespace GameSystems {
	class ObjectFactory;
}

namespace GameComponents {
	class TimerComponent : public BaseComponent
	{
		friend class ::GameSystems::ObjectFactory;
	public:
		TimerComponent(GameObjects::BaseGameObject*);
		~TimerComponent();

		virtual COMPONENT_TYPE			getType() const;
		virtual void					Update(double);
		virtual void					Init();
		virtual void					sendMessage(GameMessage::Message*);

		void							setTimerType(GameObjects::ProjectileType);
		void							setTime(double);

		void							startTimer();
		void							stopTimer();

		void							deathTime();
		void							invincibleTime();
		void							stopDash();
	private:
		GameObjects::ProjectileType		timerType;
		double							time;
		double							savedTime;
		bool							timing;

	};
}

