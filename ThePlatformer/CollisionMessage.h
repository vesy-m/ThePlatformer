#pragma once
#include "vectorMessage.h"

namespace GameMessage {
	class CollisionMessage : Message
	{
	public:
		CollisionMessage(glm::vec2 velocity, glm::vec2 position);
		~CollisionMessage();

	public:
		glm::vec2 velocity;
		glm::vec2 position;
	};
}