#include "BaseGameObject.h"

namespace GameObjects {
	BaseGameObject::BaseGameObject()
	{
		this->componentsList = std::vector<GameComponents::BaseComponent*>();
		x = 0;
		y = 0;
		height = 0;
		width = 0;
		depth = 0;
		rotate = 0;
		scale = 1;
		type = objectType::NONE;
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

	void BaseGameObject::sendMessage(Message *message)
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
		if (x < 0) this->x = 1;
		else if (x + this->getWidth() >= 1280) this->x = 1280 - this->getWidth();
		else this->x = x;

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
	void BaseGameObject::setDepth(int depth)
	{
		this->depth = depth;
	}
	int BaseGameObject::getDepth()
	{
		return this->depth;
	}
	void BaseGameObject::setHeight(int height)
	{
		this->height = height * scale;
	}
	void BaseGameObject::setWidth(int width)
	{
		this->width = width * scale;
	}
	void BaseGameObject::setScale(float scale)
	{
		this->scale = scale;
	}
	float BaseGameObject::getScale()
	{
		return this->scale;
	}
	void BaseGameObject::setRotate(int rotate)
	{
		this->rotate = rotate;
	}
	int BaseGameObject::getRotate()
	{
		return this->rotate;
	}
	void BaseGameObject::setName(std::string name)
	{
		this->name = name;
	}
	std::string BaseGameObject::getName()
	{
		return name;
	}
	void BaseGameObject::setType(objectType newtype)
	{
		this->type = newtype;
	}
	objectType BaseGameObject::getType()
	{
		return this->type;
	}
}
