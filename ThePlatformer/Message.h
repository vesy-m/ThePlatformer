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
		COLLISION = 4,
		DEBUGVECTOR = 5,
	};

	Message();
	Message(MessageId);
	~Message();

	MessageId id;
};

