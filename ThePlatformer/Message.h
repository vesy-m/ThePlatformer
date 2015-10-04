#pragma once

class Message
{

public:

	enum MessageId
	{
		JUMP = 0,
		LEFT = 1,
		RIGHT = 2,
		DEFAULT = 3,
		DEBUGVECTOR = 4

	};

	Message(MessageId);
	~Message();

	MessageId id;
};

