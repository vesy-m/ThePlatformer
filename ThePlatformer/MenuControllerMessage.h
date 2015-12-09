#pragma once
#include "Message.h"

namespace GameMessage {
	class MenuControllerMessage : public Message
	{
	public:
		MenuControllerMessage(MessageId, int);
		~MenuControllerMessage();
		int idController;
	};
}