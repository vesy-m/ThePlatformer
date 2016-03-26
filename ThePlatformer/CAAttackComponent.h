#pragma once

#include "BaseGameObject.h"

namespace GameObjects
{
	class BaseGameObject;
}

namespace GameComponents
{
	class							CAAttackComponent : public BaseComponent
	{
	public:
		CAAttackComponent(GameObjects::BaseGameObject *);
		virtual ~CAAttackComponent();

		virtual void				Update(double);
		virtual void				Init() = 0;
		virtual void				sendMessage(GameMessage::Message *) = 0;

		virtual COMPONENT_TYPE		getType() const;

	private:
		double						_cooldownA1;
		double						_cooldownA2;
		double						_cooldownA3;
	};
}