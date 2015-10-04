#pragma once
#include "Message.h"
#include "glm/glm.hpp"

class vectorMessage : Message
{
public:
	vectorMessage(MessageId, glm::vec2 vector);
	~vectorMessage();
	glm::vec2 vector;
};

