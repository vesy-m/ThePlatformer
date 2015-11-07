#include "Message.h"

namespace GameMessage {
	Message::Message(MessageId id)
	{
		this->id = id;
	}

	Message::~Message()
	{
	}
}

