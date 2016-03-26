#pragma once

#include <glm/glm.hpp>

#include "BaseGameObject.h"
#include "ObjectFactory.h"


namespace GameObjects
{
	class BaseGameObject;
}

namespace										GameComponents
{
	enum Attack
	{
		ATTACK1,
		ATTACK2,
		ATTACK3
	};

	class										CAAttackComponent : public BaseComponent
	{
	public:
		CAAttackComponent(GameObjects::BaseGameObject *);
		virtual ~CAAttackComponent();

		virtual void							Update(double);
		virtual void							Init() = 0;
		virtual void							sendMessage(GameMessage::Message *) = 0;
		virtual GameObjects::BaseGameObject		*createProjectile(GameObjects::BaseGameObject *, Attack const, float, glm::vec2) = 0;

		virtual COMPONENT_TYPE					getType() const;

	private:
		virtual void							Attack1() = 0;
		virtual void							Attack2() = 0;
		virtual void							Attack3() = 0;

		double									_cooldownA1;
		double									_cooldownA2;
		double									_cooldownA3;
	};
}