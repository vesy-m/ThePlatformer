#pragma once

#include "CAAttackComponent.h"
#include "InputComponent.h"

namespace GameSystems {
	class ObjectFactory;
}

namespace GameComponents {
	class SpriteComponent;
	class InputComponent;
}

namespace								GameComponents
{
	class								BaseballAttack : public CAAttackComponent
	{
	public:
		BaseballAttack(GameObjects::BaseGameObject *);
		~BaseballAttack();

		void							Init();
		void							sendMessage(GameMessage::Message *);

	private:
		void							Attack1();
		void							Attack2();
		void							Attack3();
		void							Attack3Released();
		GameObjects::BaseGameObject		*createProjectile(GameObjects::BaseGameObject *, GameObjects::ProjectileType const, float, glm::vec2, std::string);

		bool							isAtt3;
		bool							revert;
	};
}

