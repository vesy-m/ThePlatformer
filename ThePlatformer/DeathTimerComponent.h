#pragma once

#include "BaseGameObject.h"

namespace GameSystems {
	class ObjectFactory;
}

namespace GameComponents {
	class DeathTimerComponent : public BaseComponent
	{
		friend class ::GameSystems::ObjectFactory;
	public:
		DeathTimerComponent(GameObjects::BaseGameObject*);
		~DeathTimerComponent();

		virtual COMPONENT_TYPE			getType() const;
		virtual void					Update(double);
		virtual void					Init();
		virtual void					sendMessage(GameMessage::Message*);

		void							setDeathTime(double);

	private:
		double							deathTime;
		double							savedTime;

	};
}

