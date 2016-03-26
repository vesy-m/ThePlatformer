#pragma once
#include "CAAttackComponent.h"
namespace GameSystems {
	class ObjectFactory;
}

namespace GameComponents {
	class BaseballAttack : public CAAttackComponent
	{
	public:
		BaseballAttack(GameObjects::BaseGameObject *);
		~BaseballAttack();

		void				Init();
		void				sendMessage(GameMessage::Message *);

		void				Attack1();
		void				Attack2();
		void				Attack3();
	};
}

