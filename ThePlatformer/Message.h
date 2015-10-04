#pragma once

class Message
{

public:

	enum MessageId
	{
		JUMP,
		JUMP_RELEASED,
		LEFT,
		LEFT_RELEASED,
		RIGHT,
		RIGHT_RELEASED,
		DEFAULT,
		DEBUGVECTOR,


	};

	Message(MessageId);
	~Message();

	MessageId id;
};

