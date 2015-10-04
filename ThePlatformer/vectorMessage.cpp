#include "vectorMessage.h"



vectorMessage::vectorMessage(MessageId id, glm::vec2 vector) : Message(id)
{
	this->vector = vector;
}


vectorMessage::~vectorMessage()
{
}
