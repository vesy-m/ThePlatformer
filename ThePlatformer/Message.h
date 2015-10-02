#pragma once

class Message
{

public:

	enum MessageId
	{
		JUMP = 0,
		LEFT = 1,
		RIGHT = 2
	};

	Message(MessageId);
	~Message();

	MessageId id;
};

