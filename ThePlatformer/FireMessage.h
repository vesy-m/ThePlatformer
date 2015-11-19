#pragma once
#include "Message.h"

namespace GameMessage {
	class FireMessage : public Message {
	public:
		FireMessage();
		~FireMessage();
	};
}