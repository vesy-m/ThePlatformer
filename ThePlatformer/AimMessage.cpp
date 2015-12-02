#include "AimMessage.h"


namespace GameMessage {

	AimMessage::AimMessage(glm::vec2 drawPoint) : Message(AIM)
	{
		this->drawPoint = drawPoint;
	}


	AimMessage::~AimMessage()
	{
	}
}
