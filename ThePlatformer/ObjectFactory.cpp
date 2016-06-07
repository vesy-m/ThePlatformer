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
#include "TennisAttack.h"
#include "BoxerAttack.h"
#include "EditorManager.h"
#include "LifeBarComponent.h"
#include "AutoPlayComponent.h"
#include "InGameBannerComponent.h"

namespace GameSystems {
	ObjectFactory::ObjectFactory()
	{
		stateGame = gameState::NONE;
		systemNeedReinit = true;
		listLevels = std::vector<GameEngine::Core::Level>();
		listPlayers = std::vector<GameObjects::BaseGameObject *>();
		this->nbPlayerReady = 0;
		this->countObjects = 0;
		this->waitAMoment = false;
		clearRound();
		this->to_wait = 0;
		for (int i = 0; i < 4; i++) {
			GameObjects::BaseGameObject *skull = new GameObjects::BaseGameObject();
			new GameComponents::SpriteComponent(skull, "./assets/sprite/skull.png");
			skull->setDepth(0);
			skull->setScale(0.1f);
			skull->setY(-50);
			skull->Init();
			this->listSkull.push_back(skull);
		}
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
			else if (std::string(it->key) == "move_speed") ret->setMoveSpeed((float)it->value.toNumber());
			else if (std::string(it->key) == "bounce") ret->setBounce((float)it->value.toNumber());
			else if (std::string(it->key) == "rotate") ret->setRotate((int) it->value.toNumber());
			else if (std::string(it->key) == "width") ret->setWidth((int) it->value.toNumber());
			else if (std::string(it->key) == "height") ret->setHeight((int) it->value.toNumber());
			//else if (std::string(it->key) == "projectile_type") ret->setProjectileType(it->value.toString());
			else if (std::string(it->key) == "name") ret->setName(std::string(it->value.toString() + std::to_string(countObjects++)));
			else if (std::string(it->key) == "type") ret->setType((GameObjects::objectType)(int)it->value.toNumber());
			else if (std::string(it->key) == "sprite") new GameComponents::SpriteComponent(ret, it->value.toString());
			else if (std::string(it->key) == "fps") new GameComponents::TextComponent(ret);
			else if (std::string(it->key) == "autoplay") new GameComponents::AutoPlayComponent(ret);
			else if (std::string(it->key) == "body") new GameComponents::BodyComponent(ret);
			else if (std::string(it->key) == "boxcollider") new GameComponents::BoxCollider(ret);
			else if (std::string(it->key) == "circlecollider") new GameComponents::CircleCollider(ret);
			else if (std::string(it->key) == "controller") new GameComponents::ControllerInputComponent(ret, it->value.toString());
			else if (std::string(it->key) == "keyboard") new GameComponents::KeyboardInputComponent(ret, it->value.toString());
			else if (std::string(it->key) == "vector") new GameComponents::VectorDebugComponent(ret, it->value.toString());
			else if (std::string(it->key) == "fire_ball" && std::string(it->value.toString()) == "baseball") new GameComponents::BaseballAttack(ret);
			else if (std::string(it->key) == "fire_ball" && std::string(it->value.toString()) == "rugby") new GameComponents::RugbyManAttack(ret);
			else if (std::string(it->key) == "fire_ball" && std::string(it->value.toString()) == "tennis") new GameComponents::TennisAttack(ret);
			else if (std::string(it->key) == "fire_ball" && std::string(it->value.toString()) == "boxe") new GameComponents::BoxerAttack(ret);
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
			else if (std::string(it->key) == "attack_1")
				ret->setAttack1Value((float)it->value.toNumber());
			else if (std::string(it->key) == "attack_2")
				ret->setAttack2Value((float)it->value.toNumber());
			else if (std::string(it->key) == "attack_3")
				ret->setAttack3Value((float)it->value.toNumber());

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

	GameObjects::BaseGameObject *ObjectFactory::createProjectile(GameObjects::BaseGameObject *projectile) {
		this->currentLevel.putObjectDepthOrdered(projectile);
		return (projectile);
	}

	std::list<GameObjects::BaseGameObject*> ObjectFactory::createListObjectFromLevel(GameTools::JsonValue &value) {
		assert(value.getTag() == GameTools::JSON_OBJECT);
		std::list<GameObjects::BaseGameObject*> listGameObjects;
		for (auto i : value) {
			if (std::string(i->key) == "objects") {
				auto arr = i->value;
				assert(arr.getTag() == GameTools::JSON_ARRAY);
				for (auto j : arr) {
					auto obj = parseObject(j->value);
					listGameObjects.push_back(obj);
				}
			}
		}
		return listGameObjects;
	}

	void ObjectFactory::buildLevel(GameTools::JsonValue &value) {
		assert(value.getTag() == GameTools::JSON_OBJECT);
		GameEngine::Core::Level newLevel = GameEngine::Core::Level();

		auto object = new GameObjects::BaseGameObject();
		object->setName("readyimg");
		object->setX(0);
		object->setY(0);
		new GameComponents::SpriteComponent(object, "./assets/sprite/ready2.png");
		new GameComponents::InGameBannerComponent(object, GameComponents::START_GAME, 2000);
		newLevel.putObjectDepthOrdered(object);

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
		if (newMenu.fileName == "./config/menus/choose_level_menu.json"
			|| newMenu.fileName == "./config/menus/load_level_menu.json"
			|| newMenu.fileName == "./config/menus/delete_level_menu.json") {
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
					GameComponents::ButtonComponent *buttonComponent = NULL;
					if (newMenu.fileName == "./config/menus/load_level_menu.json") {
						buttonComponent = new GameComponents::ButtonComponent(ret, "loadLevelInEditor", "./config/levels/" + rawname + ".json");
					} else if (newMenu.fileName == "./config/menus/delete_level_menu.json") {
						buttonComponent = new GameComponents::ButtonComponent(ret, "deleteLevel", "./config/levels/" + rawname + ".json");
					} else {
						buttonComponent = new GameComponents::ButtonComponent(ret, "level", "./config/levels/" + rawname + ".json");
					}
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
						//{ifSelectedAtStart, LeftButtonPlace, RightButtonPlace, TopButtonPlace, BottomButtonPlace, levelPlaceInList, NbLevelsInList}
						int value[7] = {1, prevNb, nextNb, -1, -1, nbFileFind, nbFiles};
						buttonComponent->setNav(value, 7);
					}
					else {
						int value[7] = {0, prevNb, nextNb, -1, -1, nbFileFind, nbFiles};
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
		for each (int idController in this->orderPlayerController) {
			std::string value = this->mapPlayersController[idController];
			GameSystems::JSONParser fileParser(value);
			GameObjects::BaseGameObject* newPlayer = parseObject(fileParser.getJSONValue());
			GameComponents::InputComponent *component = nullptr;
			if (idController == 8) component = new GameComponents::KeyboardInputComponent(newPlayer, "./config/controllers/input_keyboard1.json");
			else component = new GameComponents::ControllerInputComponent(newPlayer, "./config/controllers/input_controller1.json", idController);
			component->SetActive(false);
			new GameComponents::LifeBarComponent(newPlayer, i - 1);
			newPlayer->setY(100);
			newPlayer->setX(add * i);
			this->currentLevel.putObjectDepthOrdered(newPlayer);
			listPlayers.push_back(newPlayer);
			int XCoord = add * i - 50;
			for (int round = 0; round < 2; round++) {
				GameObjects::BaseGameObject* dotRound = new GameObjects::BaseGameObject();
				std::string pathFile;
				if (round == 0 && roundWin[i - 1] >= 1) {
					pathFile += "./assets/sprite/dotRoundFull";
				}
				else if (round == 1 && roundWin[i - 1] == 2) {
					pathFile += "./assets/sprite/dotRoundFull";
				}
				else {
					pathFile += "./assets/sprite/dotRoundEmpty";
				}
				pathFile += std::to_string(i);
				pathFile += ".png";
				new GameComponents::SpriteComponent(dotRound, pathFile);
				dotRound->setY(-50);
				dotRound->setX(XCoord);
				dotRound->setDepth(0);
				dotRound->setScale(0.1f);
				this->currentLevel.putObjectDepthOrdered(dotRound);
				listDotRound.push_back(dotRound);
				XCoord += 75;
			}
			i++;
		}

	}

	void ObjectFactory::LoadMenuFileAsCurrent(const std::string &filename) {
		if (filename != "./config/menus/delete_level_menu.json" && filename == this->currentMenu.fileName && this->stateGame == gameState::MENU) return;
		countObjects = 0;
		std::string currentMenuFileName = filename;
		GameSystems::JSONParser fileParser(filename);
		this->buildMenu(fileParser.getJSONValue(), currentMenuFileName);
		this->stateGame = gameState::MENU;
		systemNeedReinit = true;
		if (this->currentMenu.fileName == "./config/menus/player_win_menu_1.json"
			|| this->currentMenu.fileName == "./config/menus/player_win_menu_2.json"
			|| this->currentMenu.fileName == "./config/menus/player_win_menu_3.json") {
			waitAMoment = true;
		}
	}

	void ObjectFactory::clearRound() {
		roundWin[0] = 0;
		roundWin[1] = 0;
		roundWin[2] = 0;
		roundWin[3] = 0;
		playerIsDead[0] = false;
		playerIsDead[1] = false;
		playerIsDead[2] = false;
		playerIsDead[3] = false;
		for each (GameObjects::BaseGameObject *skull in listSkull) {
			skull->setY(-50);
		}
		listDotRound.clear();
	}

	void ObjectFactory::LoadLevelEditor() {
		GameTools::EditorManager::getInstance();

		this->stateGame = gameState::EDITOR;
		systemNeedReinit = true;
	}

	void ObjectFactory::LoadLevelEditorWithLevel(std::string levelPath) {
		GameSystems::JSONParser fileParser(levelPath);
		std::list<GameObjects::BaseGameObject*> objects = createListObjectFromLevel(fileParser.getJSONValue());
		GameTools::EditorManager::getInstance().LoadLevel(objects);
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

	void ObjectFactory::killPlayerByObject(GameObjects::BaseGameObject * player) {
		if (player->getType() == GameObjects::objectType::PLAYER
			|| player->getType() == GameObjects::objectType::PLAYER_ATTACK 
			|| player->getType() == GameObjects::objectType::PLAYER_BLOCK) {
			player->destroy(true);
			int idPlayer = getPlayerId(player);
			playerIsDead[idPlayer] = true;
		}
		
	}

	void ObjectFactory::cleanupObjects(void) {
		std::list<GameObjects::BaseGameObject*> &list = this->currentLevel.getObjects();
		//std::cout << "Size before : "<< list.size() << std::endl;
		list.erase(std::remove_if(list.begin(), list.end(), [&](auto obj) {
			if (obj->destroy()) {
				delete obj;
				return true;
			}
			return false;
		}), list.end());
		//std::cout << "Size after : " << list.size() << std::endl;
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
		this->orderPlayerController.clear();
	}

	void ObjectFactory::addOrChangePlayerWithController(int idController, int idPerso) {
		std::stringstream filenameConfigPlayer;
		filenameConfigPlayer << "./config/players/player" << idPerso << ".json";
		if (this->mapPlayersController.find(idController) == this->mapPlayersController.end()) {
			this->orderPlayerController.push_back(idController);
		}
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
		else if (this->mapPlayersController.size() == 1 && this->nbPlayerReady == this->mapPlayersController.size()) {
			this->orderPlayerController.push_back(7);
			this->mapPlayersController[7] = "./config/players/player1.json";
			this->orderPlayerController.push_back(6);
			this->mapPlayersController[6] = "./config/players/player1.json";
			this->LoadMenuFileAsCurrent("./config/menus/choose_level_menu.json");
		}
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
		this->orderPlayerController.clear();
		this->listPlayers.clear();
		this->nbPlayerReady = 0;
		clearRound();
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
				killPlayerByObject(player);
	}

	void ObjectFactory::checkWinCondition()
	{
		if (listPlayers.empty())
			return;
		auto winPlayer = isPLayersAlive();

		if (winPlayer == nullptr)
			return;

		int idWinner = getPlayerId(winPlayer);
		roundWin[idWinner] ++;

		if (roundWin[idWinner] < 2) {
			listPlayers.clear();
			listDotRound.clear();
			playerIsDead[0] = false;
			playerIsDead[1] = false;
			playerIsDead[2] = false;
			playerIsDead[3] = false;
			for each (GameObjects::BaseGameObject *skull in listSkull) {
				skull->setY(-50);
			}
			LoadLevelFileAsCurrent(currentLevelFileName);
			return;
		}
		
		this->idWinPlayer = this->getPlayerId(winPlayer);
		listPlayers.clear();
		if (winPlayer->getName().find("baseballPlayer") != std::string::npos) {
			GameSystems::GraphicsSystem::Camera::getInstance().reInit();
			GameSystems::ObjectFactory::getInstance().LoadMenuFileAsCurrent("./config/menus/player_win_menu_1.json");
			GameSystems::AudioSystem::_menuVictory = true;
		} else if (winPlayer->getName().find("footballPlayer") != std::string::npos) {
			GameSystems::GraphicsSystem::Camera::getInstance().reInit();
			GameSystems::ObjectFactory::getInstance().LoadMenuFileAsCurrent("./config/menus/player_win_menu_2.json");
			GameSystems::AudioSystem::_menuVictory = true;
		}
		else if (winPlayer->getName().find("tennisPlayer") != std::string::npos) {
			GameSystems::GraphicsSystem::Camera::getInstance().reInit();
			GameSystems::ObjectFactory::getInstance().LoadMenuFileAsCurrent("./config/menus/player_win_menu_3.json");
			GameSystems::AudioSystem::_menuVictory = true;
		}
		else if (winPlayer->getName().find("boxerPlayer") != std::string::npos) {
			GameSystems::GraphicsSystem::Camera::getInstance().reInit();
			GameSystems::ObjectFactory::getInstance().LoadMenuFileAsCurrent("./config/menus/player_win_menu_4.json");
			GameSystems::AudioSystem::_menuVictory = true;
		}
		clearRound();
	}

	int			ObjectFactory::getPlayerId(GameObjects::BaseGameObject * player) {
		int var = (int)(find(this->listPlayers.begin(), this->listPlayers.end(), player) - this->listPlayers.begin());
		return var;
	}


	GameObjects::BaseGameObject * ObjectFactory::isPLayersAlive()
	{
		GameObjects::BaseGameObject *winner = nullptr;
		int id = 0;
		int nbAlive = 0;
		for (auto player : listPlayers) {
			if (playerIsDead[id] == false) {
				winner = player;
				nbAlive++;
			}
			id++;
		}
		if (nbAlive == 0) {
			return listPlayers.at(0);
		}
		if (nbAlive == 1) {
			return winner;
		}
		return nullptr;
	}
}
