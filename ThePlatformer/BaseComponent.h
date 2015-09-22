#pragma once
#ifndef _BASECOMPONENT_H_
#define _BASECOMPONENT_H_

#include <iostream>
#include "BaseGameObject.h"
class BaseGameObject;

class BaseComponent
{
public:
	BaseComponent();
	~BaseComponent();
private:
	BaseGameObject *composition;
};

#endif // !_BASECOMPONENT_H_