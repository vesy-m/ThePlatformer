#include "gason.h"
#include "SpriteComponent.h"
#include "ObjectFactory.h"
#include "InputComponent.h"
#include "BodyComponent.h"
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
			else if (std::string(it->key) == "width") ret->setWidth(it->value.toNumber());
			else if (std::string(it->key) == "height") ret->setWidth(it->value.toNumber());
			else if (std::string(it->key) == "sprite") {
				auto sprite = new GameComponents::SpriteComponent(ret, it->value.toString());
				ret->attachComponent((GameComponents::BaseComponent*)sprite);
			}
			else if (std::string(it->key) == "body") {
				auto body = new GameComponents::BodyComponent(ret);
				ret->attachComponent((GameComponents::BaseComponent*) body);
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

	void ObjectFactory::buildLevel(JsonValue &value, std::list<GameObjects::BaseGameObject*> &list) {
		assert(value.getTag() == JSON_OBJECT);
		for (auto i : value) {
			if (std::string(i->key) == "objects") {
				auto arr = i->value;
				assert(arr.getTag() == JSON_ARRAY);
				for (auto j : arr) {
					auto obj = parseObject(j->value);
					if (obj != NULL) list.push_back(obj);
				}
			}
		}
	}
}
