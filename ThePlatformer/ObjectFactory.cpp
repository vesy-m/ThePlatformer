#include "gason.h"
#include "BaseComponent.h"
#include "SpriteComponent.h"
#include "ObjectFactory.h"
#include "ControllerInputComponent.h"
#include "KeyboardInputComponent.h"
#include "BodyComponent.h"
#include "Collider.h"
#include "VectorDebugComponent.h"
#include "TextComponent.h"

namespace GameSystems {
	ObjectFactory::ObjectFactory()
	{
		listLevels = std::vector<Level>();
	}


	ObjectFactory::~ObjectFactory()
	{
	}

	GameObjects::BaseGameObject *ObjectFactory::parseObject(JsonValue &value) {
		assert(value.getTag() == JSON_OBJECT);
		auto ret = new GameObjects::BaseGameObject();

		for (auto it : value) {
			if (std::string(it->key) == "x") ret->setX((int) it->value.toNumber());
			else if (std::string(it->key) == "y") ret->setY((int) it->value.toNumber());
			else if (std::string(it->key) == "depth") ret->setDepth((int) it->value.toNumber());
			else if (std::string(it->key) == "scale") ret->setScale((float) it->value.toNumber());
			else if (std::string(it->key) == "rotate") ret->setRotate((int) it->value.toNumber());
			else if (std::string(it->key) == "width") ret->setWidth((int) it->value.toNumber());
			else if (std::string(it->key) == "height") ret->setHeight((int) it->value.toNumber());
			else if (std::string(it->key) == "name") ret->setName(it->value.toString());
			else if (std::string(it->key) == "type") ret->setType((GameObjects::objectType)(int)it->value.toNumber());
			else if (std::string(it->key) == "sprite") {
				auto sprite = new GameComponents::SpriteComponent(ret, it->value.toString());
			}
			else if (std::string(it->key) == "fps") {
				auto fps = new GameComponents::TextComponent(ret);
			}
			else if (std::string(it->key) == "body") {
				auto body = new GameComponents::BodyComponent(ret);
			}
			//else if (std::string(it->key) == "hexacollider") {
			//	auto vector = new GameComponents::HexagonCollider(ret);
			//	ret->attachComponent((GameComponents::BaseComponent*) vector);
			//}
			else if (std::string(it->key) == "boxcollider") {
				auto vector = new GameComponents::BoxCollider(ret);
			}
			else if (std::string(it->key) == "circlecollider") {
				auto vector = new GameComponents::CircleCollider(ret);
			}
			else if (std::string(it->key) == "joystick") {
				auto input = new GameComponents::ControllerInputComponent(ret, it->value.toString());
			}
			else if (std::string(it->key) == "keyboard") {
				auto input = new GameComponents::KeyboardInputComponent(ret, it->value.toString());
			}
			else if (std::string(it->key) == "vector") {
				auto vector = new GameComponents::VectorDebugComponent(ret);
			}
		}
		return (ret);
	}

	void ObjectFactory::attachObject(GameObjects::BaseGameObject *obj) {
		ObjectFactory::getInstance().currentLevel.putObjectDepthOrdered(obj);
	}

	GameObjects::BaseGameObject *ObjectFactory::createArrow(unsigned int x, unsigned int y) {
		auto arrow = new GameObjects::BaseGameObject();
		arrow->setName("arrow");
		arrow->setX(x);
		arrow->setY(y);
		arrow->setHeight(76 * 0.25f);
		arrow->setWidth(150 * 0.25f);
		arrow->setScale(0.25f);
		arrow->setDepth(0);
		arrow->setType(GameObjects::objectType::PROJECTILE);

		auto sprite = new GameComponents::SpriteComponent(arrow, "minecraft_arrow.png");
		sprite->Init();

		auto box = new GameComponents::BoxCollider(arrow);
		box->Init();

		auto vector = new GameComponents::VectorDebugComponent(arrow);
		vector->Init();

		auto body = new GameComponents::BodyComponent(arrow);
		body->Init();
		
		ObjectFactory::getInstance().currentLevel.putObjectDepthOrdered(arrow);
		return (arrow);
	}

	void ObjectFactory::buildLevel(JsonValue &value) {
		assert(value.getTag() == JSON_OBJECT);
		Level newLevel = Level();
		for (auto i : value) {
			if (std::string(i->key) == "objects") {
				auto arr = i->value;
				assert(arr.getTag() == JSON_ARRAY);
				for (auto j : arr) {
					auto obj = parseObject(j->value);
					if (obj != NULL) newLevel.putObjectDepthOrdered(obj);
				}
			}
		}
		currentLevel = newLevel;
	}

	void ObjectFactory::putObjectDepthOrdered(GameObjects::BaseGameObject * obj) {
		assert(obj != NULL);
		int depth = obj->getDepth();
		int size = (int) this->listGameObject.size();
		

		for (std::list<GameObjects::BaseGameObject *>::iterator it = this->listGameObject.begin(); it != this->listGameObject.end(); ++it) {
			if ((*it)->getDepth() <= depth) {
				this->listGameObject.insert(it, obj);
				return;
			}
		}
		this->listGameObject.push_back(obj);
	}

	void ObjectFactory::cleanupObjects(void) {
		std::list<GameObjects::BaseGameObject*> &list = this->currentLevel.getObjects();
		list.erase(std::remove_if(list.begin(), list.end(), [](auto obj) {
			if (obj->destroy()) {
				delete obj;
				return true;
			}
			return false;
		}), list.end());
	}

	Level &ObjectFactory::getCurrentLevel()
	{
		return this->currentLevel;
	}
}
