#include "CollisionMessage.h"

namespace GameMessage {
	CollisionMessage::CollisionMessage(glm::vec2 velocity, glm::vec2 position, glm::vec2 normal) : Message(COLLISION)
	{
		this->velocity = velocity;
		this->position = position;
		this->normal = normal;
	}

	CollisionMessage::~CollisionMessage()
	{
	}
}