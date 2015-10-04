#include "VectorMessage.h"



VectorMessage::VectorMessage(MessageId id, glm::vec2 vector) : Message(id)
{
	this->vector = vector;
}


VectorMessage::~VectorMessage()
{
}
