#pragma once

class Message
{

public:

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
		DEBUGVECTOR,
		SHOW_DEBUG,
		COLLISION,
		NO_COLLISION,
		ROTATE_LEFT,
		ROTATE_RIGHT
	};

	Message(MessageId);
	~Message();

	MessageId id;
};

