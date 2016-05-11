#pragma once
#include "Message.h"

namespace GameMessage {
	class DamageMessage : public Message
	{
	public:
		enum DamageType {
			DASH,
			PROJECTILE
		};

		DamageMessage(DamageType, int);
		~DamageMessage();
		int damage;
		DamageType damageType;
	};
}
