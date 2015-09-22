#pragma once
#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "BaseGameObject.h"
#include <vector>

class System
{
public:
	virtual void Update(float dt, std::vector<BaseGameObject>) = 0;
	virtual void Init(void) = 0;
	virtual void SendMessage() = 0;
	virtual ~System() {}
};

#endif // !_SYSTEM_H_