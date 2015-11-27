#include "gason.h"
#include "BaseComponent.h"
#include "SpriteComponent.h"
#include "ObjectFactory.h"
#include "ControllerInputComponent.h"
#include "KeyboardInputComponent.h"
#include "BodyComponent.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "VectorDebugComponent.h"
#include "TextComponent.h"
#include "ButtonComponent.h"
#include "MouseClickComponent.h"
#include "FireBallComponent.h"

namespace GameSystems {
	ObjectFactory::ObjectFactory()
	{
		stateGame = gameState::NONE;
		systemNeedReinit = true;
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
			else if (std::string(it->key) == "sprite") new GameComponents::SpriteComponent(ret, it->value.toString());
			else if (std::string(it->key) == "fps") new GameComponents::TextComponent(ret);
			else if (std::string(it->key) == "body") new GameComponents::BodyComponent(ret);
			else if (std::string(it->key) == "boxcollider") new GameComponents::BoxCollider(ret);
			else if (std::string(it->key) == "circlecollider") new GameComponents::CircleCollider(ret);
			else if (std::string(it->key) == "controller") new GameComponents::ControllerInputComponent(ret, it->value.toString());
			else if (std::string(it->key) == "keyboard") new GameComponents::KeyboardInputComponent(ret, it->value.toString());
			else if (std::string(it->key) == "vector") new GameComponents::VectorDebugComponent(ret, it->value.toString());
			else if (std::string(it->key) == "fire_ball") new GameComponents::FireBallComponent(ret);
			else if (std::string(it->key) == "level") {
				auto buttonLevel = new GameComponents::ButtonComponent(ret, GameComponents::ButtonComponent::ButtonType::LEVEL, it->value.toString());
				auto mouse = new GameComponents::MouseClickComponent(ret);
			}
			else if (std::string(it->key) == "menu") {
				auto buttonMenu = new GameComponents::ButtonComponent(ret, GameComponents::ButtonComponent::ButtonType::MENU, it->value.toString());
				auto mouse = new GameComponents::MouseClickComponent(ret);
			}
			else if (std::string(it->key) == "function") {
				auto buttonFunction = new GameComponents::ButtonComponent(ret, GameComponents::ButtonComponent::ButtonType::FUNCTION, it->value.toString());
				auto mouse = new GameComponents::MouseClickComponent(ret);
			}
			
			}
		return (ret);
	}

	void ObjectFactory::attachObject(GameObjects::BaseGameObject *obj) {
		ObjectFactory::getInstance().currentLevel.putObjectDepthOrdered(obj);
	}

	GameObjects::BaseGameObject *ObjectFactory::createProjectile(GameObjects::BaseGameObject *shooter, unsigned int x, unsigned int y, float base_force, glm::vec2 direction, ProjectileType) {
		GameObjects::BaseGameObject *projectile = NULL;
		GameComponents::BodyComponent *body = NULL;
		if (this->old_objects.size() == 0) {
			projectile = new GameObjects::BaseGameObject();
			projectile->setName(shooter->getName());

			projectile->setMass(50.0f);
			projectile->setDepth(0);
			projectile->setType(GameObjects::objectType::PROJECTILE);
			projectile->setBounce(0.3f);

			if (std::string("tennis").compare(shooter->getProjectileType()) == 0) {
				shooter->setCooldown(1500.0f);
				projectile->setHeight(int(30 * 0.50f));
				projectile->setWidth(int(30 * 0.50f));
				projectile->setScale(0.50f);
				projectile->setPower(20);
				new GameComponents::SpriteComponent(projectile, "./assets/sprite/tennis_ball.png");
			}
			else if (std::string("soccer").compare(shooter->getProjectileType()) == 0) {
				shooter->setCooldown(2000.0f);
				projectile->setHeight(int(30 * 0.50f));
				projectile->setWidth(int(30 * 0.50f));
				projectile->setScale(0.50f);
				projectile->setPower(35);
				new GameComponents::SpriteComponent(projectile, "./assets/sprite/soccer_ball.png");
			}
			else {
				shooter->setCooldown(2500.0f);
				projectile->setHeight(int(76 * 0.25f));
				projectile->setWidth(int(150 * 0.25f));
				projectile->setScale(0.25f);
				projectile->setPower(40);
				new GameComponents::SpriteComponent(projectile, "./assets/sprite/minecraft_arrow.png");
			}

			new GameComponents::BoxCollider(projectile);
			new GameComponents::VectorDebugComponent(projectile, "square");
			body = new GameComponents::BodyComponent(projectile);
		}
		else {
			projectile = dynamic_cast<GameObjects::BaseGameObject*>(this->old_objects.front());
			assert(projectile != NULL);
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
				auto obj = parseObject(i->value);
				if (obj != NULL) newMenu.addButton(obj);
			}
		}
		currentMenu = newMenu;
	}

	void ObjectFactory::LoadLevelFileAsCurrent(const std::string &filename) {
		GameSystems::JSONParser fileParser(filename);
		this->buildLevel(fileParser.getJSONValue());
		this->stateGame = gameState::LEVEL;
		this->currentLevelFileName = filename;
		systemNeedReinit = true;
	}

	void ObjectFactory::LoadMenuFileAsCurrent(const std::string &filename) {
		GameSystems::JSONParser fileParser(filename);
		this->buildMenu(fileParser.getJSONValue());
		this->stateGame = gameState::MENU;
		systemNeedReinit = true;
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
		if (this->stateGame == gameState::LEVEL) return this->currentLevel.getObjects();
		else if(this->stateGame == gameState::MENU)	return this->currentMenu.getObjects();
		else return this->currentLevel.getObjects();

	}

	const std::list<GameSystems::BaseSystem*>& ObjectFactory::getSystems()
	{
		if (systemNeedReinit) this->initSystems();
		return this->m_systems;
	}

	void ObjectFactory::initSystems() {
		for each (GameSystems::BaseSystem* system in this->m_systems) system->Init(this->getCurrentObjects());
		systemNeedReinit = false;
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
