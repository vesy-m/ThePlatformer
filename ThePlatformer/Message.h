#pragma once

class Message
{

public:

	enum MessageId
	{
		JUMP = 0,
		LEFT = 1,
		RIGHT = 2,
		DEBUGVECTOR = 3
	};

	Message(MessageId);
	~Message();

	MessageId id;
};

