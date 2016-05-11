#include "DamageMessage.h"


namespace GameMessage {
	DamageMessage::DamageMessage(DamageType damageType, int damage) : Message(DAMAGE)
	{
		this->damage = damage;
		this->damageType = damageType;
	}

	DamageMessage::~DamageMessage()
	{
	}
}