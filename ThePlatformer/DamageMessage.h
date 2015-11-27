#pragma once
#include "Message.h"

namespace GameMessage {
	class DamageMessage : public Message
	{
	public:
		DamageMessage(int);
		~DamageMessage();
		int damage;
	};
}
