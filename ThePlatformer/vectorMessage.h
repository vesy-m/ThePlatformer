#pragma once
#include "Message.h"
#include "glm/glm.hpp"

namespace GameMessage {
	class VectorMessage : public Message
	{
	public:
		VectorMessage(MessageId, glm::vec2);
		~VectorMessage();
		glm::vec2 vector;
	};
}