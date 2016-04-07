#pragma once
#include "Message.h"

namespace GameMessage {
	class MouseMessageWheel : public Message
	{
	public:
		MouseMessageWheel(int posX, int posY, int wheelD) : Message(MessageId::MOUSE_WHEEL) {
			this->positionX = posX;
			this->positionY = posY;
			this->wheelDelta = wheelD;
		}

		~MouseMessageWheel() {

		}

		int positionX;
		int positionY;
		int wheelDelta;
	};
}