#pragma once

class Message
{

public:

	enum MessageId
	{
		JUMP = 0,
		LEFT = 1,
		RIGHT = 2,
		COLLISION = 3,
		DEBUGVECTOR = 4,
	};

	Message();
	Message(MessageId);
	~Message();

	MessageId id;
};

