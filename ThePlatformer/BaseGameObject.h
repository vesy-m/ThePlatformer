#pragma once
#ifndef _BASEGAMEOBJECT_H_
#define _BASEGAMEOBJECT_H_

#include <vector>
#include "BaseComponent.h"
class BaseComponent;

class BaseGameObject
{
public:
	BaseGameObject();
	~BaseGameObject();
	std::vector<BaseComponent*> getComponents(std::string key);

private:
	std::vector<BaseComponent*> componentsList;
};

#endif // !_BASEGAMEOBJECT_H_