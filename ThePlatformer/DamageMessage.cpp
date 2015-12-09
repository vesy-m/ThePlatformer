#include "DamageMessage.h"


namespace GameMessage {
	DamageMessage::DamageMessage(int damage) : Message(DAMAGE)
	{
		this->damage = damage;
	}

	DamageMessage::~DamageMessage()
	{
	}
}