#include "FireMessage.h"

namespace GameMessage {
	FireMessage::FireMessage(sf::Event &eve, float duration) : Message(FIRE), eve(eve), duration(duration)
	{
	}

	FireMessage::~FireMessage() {
	}

	sf::Event &FireMessage::getEvent(void) const {
		return eve;
	}

	float FireMessage::getDuration(void) const {
		return duration;
	}
}