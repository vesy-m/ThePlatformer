#pragma once

#include <string>

namespace GameMessage {
	enum MessageId
	{
		JUMP,
		JUMP_RELEASED,
		JUMP_ANIMATION,
		LEFT,
		LEFT_RELEASED,
		LEFT_ANIMATION,
		RIGHT,
		RIGHT_RELEASED,
		RIGHT_ANIMATION,
		STAND_ANIMATION,
		DEFAULT,
		VELOCITY_VECTOR,
		SHOW_DEBUG,
		COLLISION,
		NO_COLLISION,
		ROTATE_LEFT,
		ROTATE_RIGHT,
		FIRE,
		DAMAGE,
		CLICKON,
		ENTERMENU,
		RIGHTMENU,
		LEFTMENU,
		UPMENU,
		DOWNMENU,
		SELECT_CONTROLLER_MENU,
		START_MENU,
		ECHAP_MENU,
		B_MENU,
		AIM,
	};

	class Message
	{
	public:
		Message(MessageId);
		virtual ~Message();
		MessageId id;
	};
}


