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
#include "ButtonComponent.h"

namespace GameSystems {
	ObjectFactory::ObjectFactory()
	{
		stateGame = gameState::NONE;
		listLevels = std::vector<GameEngine::Core::Level>();
	}


	ObjectFactory::~ObjectFactory()
	{
	}

	GameObjects::BaseGameObject *ObjectFactory::parseObject(GameTools::JsonValue &value) {
		assert(value.getTag() == GameTools::JSON_OBJECT);
		auto ret = new GameObjects::BaseGameObject();

		for (auto it : value) {
			if (std::string(it->key) == "x") ret->setX((int) it->value.toNumber());
			else if (std::string(it->key) == "y") ret->setY((int) it->value.toNumber());
			else if (std::string(it->key) == "depth") ret->setDepth((int) it->value.toNumber());
			else if (std::string(it->key) == "scale") ret->setScale((float) it->value.toNumber());
			else if (std::string(it->key) == "mass") ret->setMass((float)it->value.toNumber());
			else if (std::string(it->key) == "bounce") ret->setBounce((float)it->value.toNumber());
			else if (std::string(it->key) == "rotate") ret->setRotate((int) it->value.toNumber());
			else if (std::string(it->key) == "width") ret->setWidth((int) it->value.toNumber());
			else if (std::string(it->key) == "height") ret->setHeight((int) it->value.toNumber());
			else if (std::string(it->key) == "projectile_type") ret->setProjectileType(it->value.toString());
			else if (std::string(it->key) == "name") ret->setName(it->value.toString());
			else if (std::string(it->key) == "type") ret->setType((GameObjects::objectType)(int)it->value.toNumber());
			else if (std::string(it->key) == "sprite") {
				auto sprite = new GameComponents::SpriteComponent(ret, it->value.toString());
			}
			else if (std::string(it->key) == "level") {
				auto buttonLevel = new GameComponents::ButtonComponent(ret, GameComponents::ButtonComponent::ButtonType::LEVEL, it->value.toString());
			}
			else if (std::string(it->key) == "menu") {
				auto buttonMenu = new GameComponents::ButtonComponent(ret, GameComponents::ButtonComponent::ButtonType::MENU, it->value.toString());
			}
			else if (std::string(it->key) == "function") {
				auto buttonFunction = new GameComponents::ButtonComponent(ret, GameComponents::ButtonComponent::ButtonType::FUNCTION, it->value.toString());
			}
			else if (std::string(it->key) == "fps") {
				auto fps = new GameComponents::TextComponent(ret);
			}
			else if (std::string(it->key) == "body") {
				auto body = new GameComponents::BodyComponent(ret);
			}
			else if (std::string(it->key) == "boxcollider") {
				auto vector = new GameComponents::BoxCollider(ret);
			}
			else if (std::string(it->key) == "controller") {
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

	GameObjects::BaseGameObject *ObjectFactory::createArrow(GameObjects::BaseGameObject *shooter, unsigned int x, unsigned int y, float base_force, glm::vec2 direction) {
		GameObjects::Projectile *projectile = NULL;
		GameComponents::BodyComponent *body = NULL;
		if (this->old_objects.size() == 0) {
			projectile = new GameObjects::Projectile(shooter);
			projectile->setName(shooter->getName());

			projectile->setMass(50.0f);
			projectile->setDepth(0);
			projectile->setType(GameObjects::objectType::PROJECTILE);

			if (std::string("tennis").compare(shooter->getProjectileType()) == 0) {
				projectile->setHeight(int(30 * 0.50f));
				projectile->setWidth(int(30 * 0.50f));
				projectile->setScale(0.50f);
				new GameComponents::SpriteComponent(projectile, "./assets/sprite/tennis_ball.png");
			}
			else if (std::string("soccer").compare(shooter->getProjectileType()) == 0) {
				projectile->setHeight(int(30 * 0.50f));
				projectile->setWidth(int(30 * 0.50f));
				projectile->setScale(0.50f);
				new GameComponents::SpriteComponent(projectile, "./assets/sprite/soccer_ball.png");
			}
			else {
				projectile->setHeight(int(76 * 0.25f));
				projectile->setWidth(int(150 * 0.25f));
				projectile->setScale(0.25f);
				new GameComponents::SpriteComponent(projectile, "./assets/sprite/minecraft_arrow.png");
			}

			new GameComponents::BoxCollider(projectile);
			new GameComponents::VectorDebugComponent(projectile);
			body = new GameComponents::BodyComponent(projectile);
		}
		else {
			projectile = reinterpret_cast<GameObjects::Projectile*>(this->old_objects.front());
			this->old_objects.pop_front();
			projectile->destroy(false);

			body = dynamic_cast<GameComponents::BodyComponent*>(projectile->getComponent(GameComponents::PHYSIC));
		}
		assert(projectile != NULL);
		assert(body != NULL);
		projectile->setX(x);
		projectile->setY(y);
		projectile->Init();
		body->Init(base_force, direction);
		this->currentLevel.putObjectDepthOrdered(projectile);
		return (projectile);
	}

	void ObjectFactory::buildLevel(GameTools::JsonValue &value) {
		assert(value.getTag() == GameTools::JSON_OBJECT);
		GameEngine::Core::Level newLevel = GameEngine::Core::Level();
		for (auto i : value) {
			if (std::string(i->key) == "objects") {
				auto arr = i->value;
				assert(arr.getTag() == GameTools::JSON_ARRAY);
				for (auto j : arr) {
					auto obj = parseObject(j->value);
					if (obj != NULL) newLevel.putObjectDepthOrdered(obj);
				}
			}
		}
		currentLevel = newLevel;
	}

	void ObjectFactory::buildMenu(GameTools::JsonValue &value) {
		assert(value.getTag() == GameTools::JSON_OBJECT);
		Menu newMenu = Menu();
		for (auto i : value) {
			if (std::string(i->key) == "button") {
				auto arr = i->value;
				assert(arr.getTag() == GameTools::JSON_ARRAY);
				for (auto j : arr) {
					auto obj = parseObject(j->value);
					if (obj != NULL) newMenu.addButton(obj);
				}
			}
		}
		currentMenu = newMenu;
	}

	void ObjectFactory::LoadLevelFileAsCurrent(const std::string &filename) {
		GameSystems::JSONParser fileParser(filename);
		this->buildLevel(fileParser.getJSONValue());
		this->stateGame = gameState::LEVEL;
		this->initSystems();
	}

	void ObjectFactory::LoadMenuFileAsCurrent(const std::string &filename) {
		GameSystems::JSONParser fileParser(filename);
		this->buildMenu(fileParser.getJSONValue());
		this->stateGame = gameState::MENU;
		this->initSystems();
	}

	void ObjectFactory::putObjectDepthOrdered(GameObjects::BaseGameObject * obj) {
		assert(obj != NULL);
		int depth = obj->getDepth();
		int size = (int) this->old_objects.size();
		
		for (auto it = this->old_objects.begin(); it != this->old_objects.end(); ++it)
			if ((*it)->getDepth() <= depth) return (void) this->old_objects.insert(it, obj);
		this->old_objects.push_back(obj);
	}

	void ObjectFactory::cleanupObjects(void) {
		std::list<GameObjects::BaseGameObject*> &list = this->currentLevel.getObjects();
		list.erase(std::remove_if(list.begin(), list.end(), [&](auto obj) {
			if (obj->destroy()) {
				if (obj->getName() == "arrow") this->old_objects.push_back(obj);
				else delete obj;
				return true;
			}
			return false;
		}), list.end());
	}

	std::list<GameObjects::BaseGameObject*>& ObjectFactory::getCurrentObjects()
	{
		if (this->stateGame == gameState::LEVEL) {
			return this->currentLevel.getObjects();
		}
		else if(this->stateGame == gameState::MENU){
			return this->currentMenu.getObjects();
		}
		else {
			return std::list<GameObjects::BaseGameObject*>();
		}

	}

	const std::list<GameSystems::BaseSystem*>& ObjectFactory::getSystems()
	{
		return this->m_systems;
	}

	void ObjectFactory::initSystems() {
		for each (GameSystems::BaseSystem* system in this->m_systems)
			system->Init(this->getCurrentObjects());
	}

	void ObjectFactory::addSystems(GameSystems::BaseSystem *newSystem)
	{
		this->m_systems.push_back(newSystem);
	}

	GameEngine::Core::Level &ObjectFactory::getCurrentLevel()
	{
		return this->currentLevel;
	}

}
