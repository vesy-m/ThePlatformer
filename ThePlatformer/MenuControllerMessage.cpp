#include "MenuControllerMessage.h"

namespace GameMessage {
	MenuControllerMessage::MenuControllerMessage(MessageId idMessage, int idController) : Message(idMessage)
	{
		this->idController = idController;
	}

	MenuControllerMessage::~MenuControllerMessage()
	{
	}
}