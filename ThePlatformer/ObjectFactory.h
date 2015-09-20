#pragma once
#ifndef _OBJECTFACTORY_H_
#define _OBJECTFACTORY_H_

#include <vector>
#include "BaseGameObject.h"

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();


private:
	std::vector<BaseGameObject> listGameObject;
};

#endif // !_OBJECTFACTORY_H_