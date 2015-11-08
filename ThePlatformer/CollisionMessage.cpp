#include "CollisionMessage.h"

namespace GameMessage {
	CollisionMessage::CollisionMessage(glm::vec2 velocity, glm::vec2 position) : Message(COLLISION)
	{
		this->velocity = velocity;
		this->position = position;
	}

	CollisionMessage::~CollisionMessage()
	{
	}
}