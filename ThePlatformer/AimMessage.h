#pragma once
#include "Message.h"
#include "glm/glm.hpp"

namespace GameMessage {
	class AimMessage : public Message
	{
	public:
		AimMessage(glm::vec2);
		~AimMessage();

		glm::vec2 drawPoint;
	};
}

