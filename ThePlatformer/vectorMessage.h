#pragma once
#include "Message.h"
#include "glm/glm.hpp"

namespace GameMessage {
	class VectorMessage : Message
	{
	public:
		VectorMessage(MessageId, glm::vec2 vector);
		~VectorMessage();
		glm::vec2 vector;
	};
}

