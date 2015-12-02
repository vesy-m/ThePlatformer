#pragma once
#include "Message.h"

namespace GameMessage {
	class MenuControllerMessage : public Message
	{
	public:
		MenuControllerMessage(MessageId, int idController);
		~MenuControllerMessage();
		int idController;
	};
}