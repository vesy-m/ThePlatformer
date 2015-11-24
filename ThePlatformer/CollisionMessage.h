#pragma once
#ifndef _COLLISIONMESSAGE_H_
#define _COLLISIONMESSAGE_H_

#include "vectorMessage.h"

namespace GameMessage {
	class CollisionMessage : Message
	{
	public:
		CollisionMessage(glm::vec2 velocity, glm::vec2 position, glm::vec2 normal);
		~CollisionMessage();

	public:
		glm::vec2 velocity;
		glm::vec2 position;
		glm::vec2 normal;
	};
}

#endif // !_COLLISIONMESSAGE_H_

