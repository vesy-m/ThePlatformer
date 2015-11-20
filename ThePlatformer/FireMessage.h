#pragma once
#include "Message.h"
#include <SFML\Window\Event.hpp>

namespace GameMessage {
	class FireMessage : public Message {
	public:
		FireMessage(sf::Event&, float);
		~FireMessage();
		sf::Event &getEvent(void) const;
		float getDuration(void) const;
	private:
		sf::Event &eve;
		float duration;
	};
}