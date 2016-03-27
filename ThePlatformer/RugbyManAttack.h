#pragma once

#include "CAAttackComponent.h"

namespace GameSystems {
	class ObjectFactory;
}

namespace GameComponents {
	class SpriteComponent;
}

namespace								GameComponents
{
	class								RugbyManAttack : public CAAttackComponent
	{
	public:
		RugbyManAttack(GameObjects::BaseGameObject *);
		~RugbyManAttack();

		void							Init();
		void							sendMessage(GameMessage::Message *);

	private:
		void							Attack1();
		void							Attack2();
		void							Attack3();
		GameObjects::BaseGameObject		*createProjectile(GameObjects::BaseGameObject *, GameObjects::ProjectileType const, float, glm::vec2, std::string);
	};
}