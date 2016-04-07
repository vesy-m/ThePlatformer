#pragma once
#include "Message.h"

namespace GameMessage {
	class MouseMessageMove : public Message
	{
	public:
		MouseMessageMove(int posX, int posY) : Message(MessageId::MOUSE_MOVE) {
			this->positionX = posX;
			this->positionY = posY;
		}

		~MouseMessageMove() {

		}

		int positionX;
		int positionY;
	};
}