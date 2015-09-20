#pragma once
#ifndef _WINDOWINPUTSYSTEM_H_
#define _WINDOWINPUTSYSTEM_H_

#include "System.h"

class WindowInputSytem : System
{
public:
	WindowInputSytem();
	~WindowInputSytem();
	void Update(float dt, std::vector<BaseGameObject>);
	void Init(void);
	void SendMessage();

};

#endif // !_WINDOWINPUTSYSTEM_H_