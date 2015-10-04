#include "BaseGameObject.h"

namespace GameObjects {
	BaseGameObject::BaseGameObject()
	{
		this->componentsList = std::vector<GameComponents::BaseComponent*>();
		x = 0;
		y = 0;
		height = 0;
		width = 0;
	}

	BaseGameObject::~BaseGameObject()
	{
	}

	std::vector<GameComponents::BaseComponent*> BaseGameObject::getComponents(GameComponents::COMPONENT_TYPE type)
	{
		// a changer
		std::vector<GameComponents::BaseComponent*> newVect = std::vector<GameComponents::BaseComponent*>();
		for (size_t i = 0; i < this->componentsList.size(); i++)
		{
			GameComponents::BaseComponent* elem = this->componentsList.at(i);
			if (elem->getType() == type) {
				newVect.push_back(elem);
			}
		}
		return newVect;
	}
	void BaseGameObject::attachComponent(GameComponents::BaseComponent *component)
	{
		this->componentsList.push_back(component);
	}

	void BaseGameObject::SendMessage(Message *message)
	{
		for (size_t i = 0; i < this->componentsList.size(); i++) {
			//std::cout << this->componentsList.at(i)->getType() << std::endl;
			this->componentsList.at(i)->sendMessage(message);
		}
/*		for each (GameComponents::BaseComponent *component in this->componentsList)
		{
			std::cout << component->getType() << std::endl;
			component->SendMessage(message);
		}
*/	}

	void BaseGameObject::setX(int x)
	{
		this->x = x;
	}
	int BaseGameObject::getX()
	{
		return this->x;
	}
	void BaseGameObject::setY(int y)
	{
		this->y = y;
	}
	int BaseGameObject::getY()
	{
		return this->y;
	}
	int BaseGameObject::getHeight()
	{
		return this->height;
	}

	int BaseGameObject::getWidth()
	{
		return this->width;
	}
	void BaseGameObject::setHeight(int height)
	{
		this->height = height;
	}
	void BaseGameObject::setWidth(int width)
	{
		this->width = width;
	}
}
