#include "gason.h"
#include "SpriteComponent.h"
#include "ObjectFactory.h"
#include "InputComponent.h"
#include "BodyComponent.h"
#include "Collider.h"
#include "VectorDebugComponent.h"

namespace GameSystems {
	ObjectFactory::ObjectFactory()
	{
	}


	ObjectFactory::~ObjectFactory()
	{
	}

	GameObjects::BaseGameObject *ObjectFactory::parseObject(JsonValue &value) {
		assert(value.getTag() == JSON_OBJECT);
		auto ret = new GameObjects::BaseGameObject();

		for (auto it : value) {
			if (std::string(it->key) == "x") ret->setX(it->value.toNumber());
			else if (std::string(it->key) == "y") ret->setY(it->value.toNumber());
			else if (std::string(it->key) == "depth") ret->setDepth(it->value.toNumber());
			else if (std::string(it->key) == "scale") ret->setScale(it->value.toNumber());
			else if (std::string(it->key) == "rotate") ret->setRotate(it->value.toNumber());
			else if (std::string(it->key) == "width") ret->setWidth(it->value.toNumber());
			else if (std::string(it->key) == "height") ret->setHeight(it->value.toNumber());
			else if (std::string(it->key) == "name") ret->setName(it->value.toString());
			else if (std::string(it->key) == "sprite") {
				auto sprite = new GameComponents::SpriteComponent(ret, it->value.toString());
				ret->attachComponent((GameComponents::BaseComponent*)sprite);
			}
			else if (std::string(it->key) == "body") {
				auto body = new GameComponents::BodyComponent(ret);
				ret->attachComponent((GameComponents::BaseComponent*) body);
			}
			else if (std::string(it->key) == "hexacollider") {
				auto vector = new GameComponents::HexagonCollider(ret);
				ret->attachComponent((GameComponents::BaseComponent*) vector);
			}
			else if (std::string(it->key) == "boxcollider") {
				auto vector = new GameComponents::BoxCollider(ret);
				ret->attachComponent((GameComponents::BaseComponent*) vector);
			}
			else if (std::string(it->key) == "input") {
				auto input = new GameComponents::InputComponent(ret);
				ret->attachComponent((GameComponents::BaseComponent*) input);
			}
			else if (std::string(it->key) == "vector") {
				auto vector = new GameComponents::VectorDebugComponent(ret);
				ret->attachComponent((GameComponents::BaseComponent*) vector);
			}
		}
		return (ret);
	}

	void ObjectFactory::buildLevel(JsonValue &value) {
		assert(value.getTag() == JSON_OBJECT);
		for (auto i : value) {
			if (std::string(i->key) == "objects") {
				auto arr = i->value;
				assert(arr.getTag() == JSON_ARRAY);
				for (auto j : arr) {
					auto obj = parseObject(j->value);
					if (obj != NULL) putObjectDepthOrdered(obj);
				}
			}
		}
	}

	void ObjectFactory::putObjectDepthOrdered(GameObjects::BaseGameObject * obj) {
		int depth = obj->getDepth();
		int size = this->listGameObject.size();
		

		for (std::list<GameObjects::BaseGameObject *>::iterator it = this->listGameObject.begin(); it != this->listGameObject.end(); ++it) {
			if ((*it)->getDepth() <= depth) {
				this->listGameObject.insert(it, obj);
				return;
			}
		}
		this->listGameObject.push_back(obj);
	}

	std::list<GameObjects::BaseGameObject *> &ObjectFactory::getObjects()
	{
		return this->listGameObject;
	}
}
