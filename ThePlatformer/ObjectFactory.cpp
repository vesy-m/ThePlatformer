#include "gason.h"
#include "BaseComponent.h"
#include "SpriteComponent.h"
#include "AimComponent.h"
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
#include "AudioComponent.h"
#include "AudioSystem.h"
#include "BaseballAttack.h"
#include "RugbyManAttack.h"
#include "EditorManager.h"

namespace GameSystems {
	ObjectFactory::ObjectFactory()
	{
		stateGame = gameState::NONE;
		systemNeedReinit = true;
		listLevels = std::vector<GameEngine::Core::Level>();
		listPlayers = std::vector<GameObjects::BaseGameObject *>();
		this->nbPlayerReady = 0;
		this->countObjects = 0;
	}

	ObjectFactory::~ObjectFactory()
	{
	}

	GameObjects::BaseGameObject *ObjectFactory::parseObject(GameTools::JsonValue &value) {
		assert(value.getTag() == GameTools::JSON_OBJECT);
		auto ret = new GameObjects::BaseGameObject();

		GameComponents::ButtonComponent *buttonComponent = NULL;
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
			//else if (std::string(it->key) == "projectile_type") ret->setProjectileType(it->value.toString());
			else if (std::string(it->key) == "name") ret->setName(std::string(it->value.toString() + std::to_string(countObjects++)));
			else if (std::string(it->key) == "type") ret->setType((GameObjects::objectType)(int)it->value.toNumber());
			else if (std::string(it->key) == "sprite") new GameComponents::SpriteComponent(ret, it->value.toString());
			else if (std::string(it->key) == "fps") new GameComponents::TextComponent(ret);
			else if (std::string(it->key) == "body") new GameComponents::BodyComponent(ret);
			else if (std::string(it->key) == "boxcollider") new GameComponents::BoxCollider(ret);
			else if (std::string(it->key) == "circlecollider") new GameComponents::CircleCollider(ret);
			else if (std::string(it->key) == "controller") new GameComponents::ControllerInputComponent(ret, it->value.toString());
			else if (std::string(it->key) == "keyboard") new GameComponents::KeyboardInputComponent(ret, it->value.toString());
			else if (std::string(it->key) == "vector") new GameComponents::VectorDebugComponent(ret, it->value.toString());
			else if (std::string(it->key) == "fire_ball" && std::string(it->value.toString()) == "baseball") new GameComponents::BaseballAttack(ret);
			else if (std::string(it->key) == "fire_ball" && std::string(it->value.toString()) == "rugby") new GameComponents::RugbyManAttack(ret);
			else if (std::string(it->key) == "sfx") new GameComponents::AudioComponent(ret, it->value.toString());
			else if (std::string(it->key) == "level" || std::string(it->key) == "menu" || std::string(it->key) == "function") {
				std::cout << it->key << std::endl;
				buttonComponent = new GameComponents::ButtonComponent(ret, std::string(it->key), it->value.toString());
				if (buttonComponent->buttonState == GameComponents::ButtonComponent::ButtonState::PLAYERCREATOR)
					new GameComponents::MouseClickComponent(ret, 1);
				else new GameComponents::MouseClickComponent(ret);
			}
			else if (std::string(it->key) == "menunav")
				buttonComponent->setNav(it->value);
			//else if (std::string(it->key) == "aim") new GameComponents::AimComponent(ret, it->value.toString());
		}
		return (ret);
	}

	void ObjectFactory::attachObject(GameObjects::BaseGameObject *obj) {
		ObjectFactory::getInstance().currentLevel.putObjectDepthOrdered(obj);
	}

	GameObjects::BaseGameObject *ObjectFactory::getUsableProjectile(GameObjects::ProjectileType projectileType) {
		GameObjects::BaseGameObject *projectile = NULL;

		if (this->old_objects.size() != 0) {
			for (auto it = this->old_objects.begin(); it != this->old_objects.end(); ++it) {
				if ((*it)->getProjectileType() == projectileType) {
					projectile = dynamic_cast<GameObjects::BaseGameObject*>(this->old_objects.front());
					assert(projectile != NULL);
					this->old_objects.remove((*it));
					projectile->destroy(false);
					return projectile;
				}
			}
			}
		return projectile;
			}

	GameObjects::BaseGameObject *ObjectFactory::createProjectile(GameObjects::BaseGameObject *projectile/*, unsigned int x, unsigned int y, float base_force, glm::vec2 direction, std::string const &sprite, bool gravity*/) {
		//GameObjects::BaseGameObject *projectile = NULL;
		//GameComponents::BodyComponent *body = NULL;
		//if (this->old_objects.size() == 0) {
		//	new GameComponents::SpriteComponent(projectile, sprite);
		//	body = dynamic_cast<GameComponents::BodyComponent*>(projectile->getComponent(GameComponents::PHYSIC));
			//projectile = new GameObjects::BaseGameObject();
			//projectile->setName(shooter->getName());
			//projectile->setDepth(0);
			//projectile->setType(GameObjects::objectType::PROJECTILE);
			//projectile->setBounce(0.3f);

			//if (std::string("tennis").compare(shooter->getProjectileType()) == 0) {
			//	projectile->setMass(25.0f);
			//	shooter->setCooldown(1500.0f);
			//	projectile->setHeight(int(30 * 0.50f));
			//	projectile->setWidth(int(30 * 0.50f));
			//	projectile->setScale(0.50f);
			//	projectile->setPower(20);
			//	new GameComponents::SpriteComponent(projectile, "./assets/sprite/tennis_ball.png");
			//}
			//else if (std::string("soccer").compare(shooter->getProjectileType()) == 0) {
			//	projectile->setMass(100.0f);
			//	shooter->setCooldown(2500.0f);
			//	projectile->setHeight(int(30 * 0.50f));
			//	projectile->setWidth(int(30 * 0.50f));
			//	projectile->setScale(0.50f);
			//	projectile->setPower(50);
			//	new GameComponents::SpriteComponent(projectile, "./assets/sprite/soccer_ball.png");
//			}
			//else {
			//	shooter->setCooldown(2500.0f);
			//	projectile->setHeight(int(76 * 0.25f));
			//	projectile->setWidth(int(150 * 0.25f));
			//	projectile->setScale(0.25f);
			//	projectile->setPower(40);
			//	new GameComponents::SpriteComponent(projectile, "./assets/sprite/minecraft_arrow.png");
//			}

		//	new GameComponents::BoxCollider(projectile);
		//	new GameComponents::VectorDebugComponent(projectile, "square");
		//}
		//else {
		//	projectile = dynamic_cast<GameObjects::BaseGameObject*>(this->old_objects.front());
		//	assert(projectile != NULL);
		//	this->old_objects.pop_front();
		//	projectile->destroy(false);
		//	body = dynamic_cast<GameComponents::BodyComponent*>(projectile->getComponent(GameComponents::PHYSIC));
		//}
		//assert(projectile != NULL);
		//assert(body != NULL);
		//projectile->setX(x);
		//projectile->setY(y);
		//projectile->Init();
		//body->Init(base_force, direction);
		//if (!gravity)
		//	body->setGravity(0);
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

	void ObjectFactory::buildMenu(GameTools::JsonValue &value, std::string &currentMenuFileName) {
		assert(value.getTag() == GameTools::JSON_OBJECT);
		Menu newMenu = Menu();
		for (auto i : value) {
			if (std::string(i->key) == "button") {
				auto obj = parseObject(i->value);
				if (obj != NULL) newMenu.addButton(obj);
			}
		}
		newMenu.prevMenu = currentMenu.fileName;
		newMenu.prevState = this->stateGame;
		newMenu.fileName = currentMenuFileName;
		std::cout << "----" << newMenu.fileName << std::endl;
		if (newMenu.fileName == "./config/menus/choose_level_menu.json") {
			int midValue = 512;
			int sizeCase = 256;
			int sizeSpace = 20;
			WIN32_FIND_DATA ffd;
			HANDLE hFind = INVALID_HANDLE_VALUE;
			int nbFiles = 0;
			hFind = FindFirstFile("./assets/levels_preview/*", &ffd);
			do
			{
				nbFiles = nbFiles + 1;
			} while (FindNextFile(hFind, &ffd) != 0);
			FindClose(hFind);
			nbFiles = nbFiles - 2;
			std::cout << nbFiles << std::endl;

			hFind = INVALID_HANDLE_VALUE;
			int idButtonInFile = 2;
			int nbFileFind = 0;
			hFind = FindFirstFile("./assets/levels_preview/*", &ffd);
			do
			{
				if ((ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == false)
				{
					auto ret = new GameObjects::BaseGameObject();
					std::string pathFile = "./assets/levels_preview/";
					pathFile += ffd.cFileName;
					std::string filePng = ffd.cFileName;
					size_t lastindex = filePng.find_last_of(".");
					std::string rawname = filePng.substr(0, lastindex);
					new GameComponents::SpriteComponent(ret, pathFile);
					ret->setScale(0.2f);
					GameComponents::ButtonComponent *buttonComponent = new GameComponents::ButtonComponent(ret, "level", "./config/levels/" + rawname + ".json");
					new GameComponents::MouseClickComponent(ret);
					int nextNb = idButtonInFile + 1;
					int prevNb = idButtonInFile - 1;
					if (nbFileFind == nbFiles - 1) {
						nextNb = -1;
					}
					if (nbFileFind == 0) {
						prevNb = -1;
					}
					if (nbFileFind == 0) {
						int value[7] = {1, prevNb, nextNb, -1, 1, nbFileFind, nbFiles};
						buttonComponent->setNav(value, 7);
					}
					else {
						int value[7] = {0, prevNb, nextNb, -1, 1, nbFileFind, nbFiles};
						buttonComponent->setNav(value, 7);
					}
					ret->setX(midValue + (sizeCase + sizeSpace) * (nbFileFind));
					ret->setY(300);

					newMenu.addButton(ret);
					idButtonInFile++;
					nbFileFind++;
				}
			} while (FindNextFile(hFind, &ffd) != 0);
			FindClose(hFind);


		}

		this->currentMenu = newMenu;
	}

	void ObjectFactory::LoadLevelFileAsCurrent(const std::string &filename) {
		GameSystems::JSONParser fileParser(filename);
		this->buildLevel(fileParser.getJSONValue());
		this->stateGame = gameState::LEVEL;
		this->currentLevelFileName = filename;
		systemNeedReinit = true;
		int i = 1;
		int add = 1280 / (int)(this->mapPlayersController.size() + 1);
		for (std::pair<int, std::string> entry : this->mapPlayersController) {
			GameSystems::JSONParser fileParser(entry.second);
			GameObjects::BaseGameObject* newPlayer = parseObject(fileParser.getJSONValue());
			if (entry.first == 8) new GameComponents::KeyboardInputComponent(newPlayer, "./config/controllers/input_keyboard1.json");
			else new GameComponents::ControllerInputComponent(newPlayer, "./config/controllers/input_controller1.json", entry.first);
			newPlayer->setY(400);
			newPlayer->setX(add * i);
			this->currentLevel.putObjectDepthOrdered(newPlayer);
			listPlayers.push_back(newPlayer);
			i++;
		}
	}

	void ObjectFactory::LoadMenuFileAsCurrent(const std::string &filename) {
		if (filename == this->currentMenu.fileName && this->stateGame == gameState::MENU) return;
		countObjects = 0;
		std::string currentMenuFileName = filename;
		GameSystems::JSONParser fileParser(filename);
		this->buildMenu(fileParser.getJSONValue(), currentMenuFileName);
		this->stateGame = gameState::MENU;
		systemNeedReinit = true;
	}

	void ObjectFactory::LoadLevelEditor() {
		GameTools::EditorManager::getInstance();

		this->stateGame = gameState::EDITOR;
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
				/*if (obj->getType() == GameObjects::PROJECTILE) this->old_objects.push_back(obj);
				else */delete obj;
				return true;
			}
			return false;
		}), list.end());
	}

	std::list<GameObjects::BaseGameObject*>& ObjectFactory::getCurrentObjects()
	{
		if (this->stateGame == gameState::LEVEL) return this->currentLevel.getObjects();
		else if(this->stateGame == gameState::MENU)	return this->currentMenu.getObjects();
		else if (this->stateGame == gameState::EDITOR)	return GameTools::EditorManager::getInstance().getObjects();
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

	bool ObjectFactory::controllerAlreadyTook(int idController)
	{
		for (std::pair<int, std::string> entry : this->mapPlayersController) {
			if (idController == entry.first)
				return true;
		}
		return false;
	}

	void ObjectFactory::removeAllPlayersWithController() {
		this->mapPlayersController.clear();
	}

	void ObjectFactory::addOrChangePlayerWithController(int idController, int idPerso) {
		std::stringstream filenameConfigPlayer;
		filenameConfigPlayer << "./config/players/player" << idPerso << ".json";
		this->mapPlayersController[idController] = filenameConfigPlayer.str();
	}

	void ObjectFactory::changeGameObjectSpriteComponent(GameObjects::BaseGameObject* obj, std::string filename) {
		GameComponents::SpriteComponent *sprite = new GameComponents::SpriteComponent(obj, filename);
		sprite->Init();
	}

	void ObjectFactory::playersReady(int nb) {
		this->nbPlayerReady += nb;
		if (this->mapPlayersController.size() > 1 && this->nbPlayerReady == this->mapPlayersController.size())
			this->LoadMenuFileAsCurrent("./config/menus/choose_level_menu.json");
		/*else if (this->mapPlayersController.size() == 1 && this->nbPlayerReady == this->mapPlayersController.size()) {
			this->mapPlayersController[6] = "./config/players/player1.json";
			this->LoadMenuFileAsCurrent("./config/menus/choose_level_menu.json");
		}*/
	}

	void ObjectFactory::changeSelectedButtonMenu(int idButton) {
		int i = 0;
		for (GameObjects::BaseGameObject *button : this->currentMenu.getObjects()) {
			if (i == idButton) {
				GameComponents::ButtonComponent * comp = (GameComponents::ButtonComponent *)button->getComponent(GameComponents::COMPONENT_TYPE::BUTTON);
				if (comp) {
					comp->toggleSelected(true);
					std::cout << i << " id selected" << std::endl;
					break;
				}
			}
			i++;
		}
	}

	void ObjectFactory::changeSelectedButtonMenu(GameObjects::BaseGameObject* button) {
		for (GameObjects::BaseGameObject *curButton : this->currentMenu.getObjects()) {
			GameComponents::ButtonComponent * comp = (GameComponents::ButtonComponent *)curButton->getComponent(GameComponents::COMPONENT_TYPE::BUTTON);
			if (comp) comp->toggleSelected(false);
		}
		GameComponents::ButtonComponent * compButton = (GameComponents::ButtonComponent *)button->getComponent(GameComponents::COMPONENT_TYPE::BUTTON);
		if (compButton) compButton->toggleSelected(true);
	}

	void ObjectFactory::clearPlayers() {
		this->mapPlayersController.clear();
		this->listPlayers.clear();
		this->nbPlayerReady = 0;
	}

	void ObjectFactory::returnPrevMenuOrResumeLevel() {
		if (this->currentMenu.prevState == gameState::LEVEL)
			GameSystems::ObjectFactory::getInstance().stateGame = GameSystems::ObjectFactory::gameState::LEVEL;
		else
			this->LoadMenuFileAsCurrent(this->currentMenu.prevMenu);
	}

	void ObjectFactory::winTheGame(std::string name)
	{
		for (auto player : listPlayers)
			if (name.compare(player->getName()) != 0)
				player->destroy(true);
	}

	void ObjectFactory::checkWinCondition()
	{
		if (listPlayers.empty())
			return;
		auto winPlayer = isPLayersAlive();

		if (winPlayer == nullptr)
			return;
		
		this->idWinPlayer = this->getPlayerId(winPlayer);
		listPlayers.clear();
		if (winPlayer->getName().find("megaman") != std::string::npos) {
			GameSystems::GraphicsSystem::Camera::getInstance().reInit();
			GameSystems::ObjectFactory::getInstance().LoadMenuFileAsCurrent("./config/menus/megaman_win_menu.json");
			GameSystems::AudioSystem::_menuVictory = true;
		}
		else {
			GameSystems::GraphicsSystem::Camera::getInstance().reInit();
			GameSystems::ObjectFactory::getInstance().LoadMenuFileAsCurrent("./config/menus/metalslug_win_menu.json");
			GameSystems::AudioSystem::_menuVictory = true;
		}
	}

	int			ObjectFactory::getPlayerId(GameObjects::BaseGameObject * player) {
		int var = (int)(find(this->listPlayers.begin(), this->listPlayers.end(), player) - this->listPlayers.begin());
		return var;
	}


	GameObjects::BaseGameObject * ObjectFactory::isPLayersAlive()
	{
		bool winCondition = false;
		GameObjects::BaseGameObject *tmpObj = nullptr;
		for (auto player : listPlayers) {
			if (!player->destroy() && !winCondition) {
				tmpObj = player;
				winCondition = true;
			}
			else if (!player->destroy() && winCondition)
				return nullptr;
		}
		return tmpObj;
	}
}
