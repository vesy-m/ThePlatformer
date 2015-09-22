#include "BaseGameObject.h"

BaseGameObject::BaseGameObject()
{
	this->componentsList = std::vector<BaseComponent*>();
	std::cout << "plop" << std::endl;
}

BaseGameObject::~BaseGameObject()
{
}

std::vector<BaseComponent*> BaseGameObject::getComponents(std::string key)
{
	return this->componentsList;
}
