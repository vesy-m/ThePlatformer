#pragma once
#include "Message.h"

namespace GameMessage {
	class MouseMessageClick : public Message
	{
	public:
		MouseMessageClick(int posX, int posY, bool lClick, bool rClick) : Message(MessageId::MOUSE_CLICK) {
			this->positionX = posX;
			this->positionY = posY;
			this->leftClick = lClick;
			this->rightClick = rClick;
		}

		~MouseMessageClick() {

		}

		int positionX;
		int positionY;
		bool rightClick;
		bool leftClick;
	};
}