#include "ButtonComponent.h"
#include "AudioSystem.h"

namespace GameComponents {

	bool ButtonComponent::actionAlreadyCompute = false;

	ButtonComponent::ButtonComponent(GameObjects::BaseGameObject* object, const std::string &buttonType, const std::string& actionName) : BaseComponent(object)
	{
		object->attachComponent(this);
		this->actionName = actionName;
		this->specialFunction = "";
		this->numPlayerSelected = 1;
		if (buttonType == "menu") { this->buttonType = ButtonType::MENU; }
		else if (buttonType == "level") { this->buttonType = ButtonType::LEVEL; }
		else if (buttonType == "function") { this->buttonType = ButtonType::FUNCTION; }
		else {
			this->specialFunction = buttonType;
		}
		this->typeMap[ButtonType::MENU] = &ButtonComponent::execMenu;
		this->typeMap[ButtonType::LEVEL] = &ButtonComponent::execLevel;
		this->typeMap[ButtonType::FUNCTION] = &ButtonComponent::execFunction;

		this->functionMap["changeResolution"] = &ButtonComponent::changeResolution;
		this->functionMap["resumeToLevel"] = &ButtonComponent::resumeToLevel;
		this->functionMap["restartLevel"] = &ButtonComponent::restartLevel;
		this->functionMap["quitGame"] = &ButtonComponent::quitGame;
		this->functionMap["prevMenu"] = &ButtonComponent::prevMenu;
		this->functionMap["backPlayer"] = &ButtonComponent::backPlayer;
		this->functionMap["backLevel"] = &ButtonComponent::backLevel;
		this->functionMap["backEditor"] = &ButtonComponent::backEditor;
		this->functionMap["switchFullScreen"] = &ButtonComponent::switchFullScreen;
		this->functionMap["startEditor"] = &ButtonComponent::startLevelEditor;
		this->functionMap["loadLevelInEditor"] = &ButtonComponent::loadLevelInEditor;
		this->functionMap["deleteLevel"] = &ButtonComponent::deleteLevel;

		this->buttonState = ButtonState::CLASSIC;
		if (actionName == "createPlayer") {
			this->buttonState = ButtonState::PLAYERCREATOR;
			GameSystems::ObjectFactory::getInstance().clearPlayers();
		}
		this->navDirection = new int[4] { -1, -1, -1, -1 };
		this->movingButton = false;
		this->numMovingButton = 0;
		this->sizeListMovingButton = 0;

	}


	ButtonComponent::~ButtonComponent()
	{
	}

	void ButtonComponent::setNav(GameTools::JsonValue &value)
	{
		if (value.getTag() != GameTools::JSON_ARRAY)
			GameTools::debugManager::getInstance().dAssert("ButtonComponent NAV not an array");
		int i = -1;
		for (auto j : value) {
			assert(i < 6);
			if (i == -1) {
				if ((int)j->value.toNumber() == 1)
					this->toggleSelected(true);
			}
			else if (i == 4) {
				this->movingButton = true;
				this->numMovingButton = (int)j->value.toNumber();
			}
			else if (i == 5) {
				this->sizeListMovingButton = (int)j->value.toNumber();
			}
			else {
				this->navDirection[i] = (int)j->value.toNumber();
			}
			i++;
		}
	}

	void ButtonComponent::setNav(int *values, int size)
	{
		int i = -1;
		for (int it = 0; it < size; it++) {
//			std::cout << values[it] << " ";
			if (i == -1) {
				if (values[it] == 1)
					this->toggleSelected(true);
			}
			else if (i == 4) {
				this->movingButton = true;
				this->numMovingButton = values[it];
			}
			else if (i == 5) {
				this->sizeListMovingButton = values[it];
			}
			else {
				this->navDirection[i] = values[it];
			}
			i++;
		}
		std::cout << std::endl;
	}

	COMPONENT_TYPE ButtonComponent::getType() const
	{
		return this->type;
	}

	void ButtonComponent::Update(double dt)
	{
		ButtonComponent::actionAlreadyCompute = false;
		float x = (float)this->composition->getX();
		float y = (float)this->composition->getY();
		float height = (float)this->composition->getHeight();
		float width = (float)this->composition->getWidth();
		if (this->buttonState == ButtonState::SELECTED)
			drawSquare(x, y, width, height);
	}

	void ButtonComponent::drawSquare(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
		glLineWidth(3);
		//glColor3f(1.0f / 256.0f * 10.0f, 1.0f / 256.0f * 200.0f, 1.0f / 256.0f * 70.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_LINES);
			//top
			glVertex2f(x, y);
			glVertex2f(x + width, y);
			//left
			glVertex2f(x, y);
			glVertex2f(x, y + height);
			//right
			glVertex2f(x + width, y);
			glVertex2f(x + width, y + height);
			//bottom
			glVertex2f(x, y + height);
			glVertex2f(x + width, y + height);
		glEnd();
		glColor3f(1.0, 1.0, 1.0);

	}

	void ButtonComponent::Init()
	{
	}

	void ButtonComponent::sendMessage(GameMessage::Message *message)
	{
		int minX = 512 - (this->composition->getWidth() - 20) * (this->sizeListMovingButton - (this->numMovingButton + 1));
		int maxX = 512 + (this->composition->getWidth() + 20) * (this->numMovingButton);
		switch (message->id)
		{
		case GameMessage::CLICKON:
			this->execAction();
			break;
		case GameMessage::START_MENU:
			if (actionName == "resumeToLevel") {
				GameSystems::AudioSystem::_pauseMenu = false;
				this->execAction();
			}
			break;
		case GameMessage::ECHAP_MENU:
			if (actionName == "resumeToLevel") {
				this->execAction();
				GameSystems::AudioSystem::_pauseMenu = false;
			} else if (actionName == "backPlayer") {
				this->backPlayer();
			} else if (actionName == "backLevel") {
				this->backLevel();
			} else if (actionName == "backEditor") {
				this->backEditor();
			}
			break;
		case GameMessage::B_MENU:
			if (actionName == "backPlayer") {
				this->backPlayer();
			} else if (actionName == "backLevel") {
				this->backLevel();
			} else if (actionName == "backEditor") {
				this->backEditor();
			}
			break;
		case GameMessage::ENTERMENU:
			if (this->buttonState == ButtonState::CHOOSEPLAYER) {
				this->buttonState = ButtonState::READYPLAYER;
				std::stringstream ss;
				ss << "./assets/sprite/menu/playerReady" << this->numPlayerSelected << ".png";
				GameSystems::ObjectFactory::getInstance().changeGameObjectSpriteComponent(this->composition, ss.str());
				GameSystems::ObjectFactory::getInstance().playersReady(1);
			}
			else if (this->buttonState == ButtonState::SELECTED) this->execAction();
			break;
		case GameMessage::LEFTMENU:
			if (this->composition->getX() < maxX && movingButton == true) {
				this->composition->setX(this->composition->getX() + this->composition->getWidth() + 20);
			}
			if (this->buttonState == ButtonState::CHOOSEPLAYER) {
				this->numPlayerSelected--;
				if (this->numPlayerSelected < 1)
					numPlayerSelected = 3;
				createPlayer(this->idPad);
			}
			else if (this->buttonState == ButtonState::SELECTED && this->navDirection[0] != -1 && ButtonComponent::actionAlreadyCompute == false) {
				this->buttonState = ButtonState::CLASSIC;
				GameSystems::ObjectFactory::getInstance().changeSelectedButtonMenu(this->navDirection[0]);
				ButtonComponent::actionAlreadyCompute = true;
			}
			break;
		case GameMessage::RIGHTMENU:
			if (this->composition->getX() > minX && movingButton == true) {
				this->composition->setX(this->composition->getX() - this->composition->getWidth() - 20);
			}
			if (this->buttonState == ButtonState::CHOOSEPLAYER) {
				this->numPlayerSelected++;
				if (this->numPlayerSelected > 3)
					numPlayerSelected = 1;
				createPlayer(this->idPad);
			}
			else if (this->buttonState == ButtonState::SELECTED && this->navDirection[1] != -1 && ButtonComponent::actionAlreadyCompute == false) {
				this->buttonState = ButtonState::CLASSIC;
				GameSystems::ObjectFactory::getInstance().changeSelectedButtonMenu(this->navDirection[1]);
				ButtonComponent::actionAlreadyCompute = true;
			}

			break;
		case GameMessage::UPMENU:
			if (this->buttonState == ButtonState::SELECTED && this->navDirection[2] != -1 && ButtonComponent::actionAlreadyCompute == false) {
				this->buttonState = ButtonState::CLASSIC;
				GameSystems::ObjectFactory::getInstance().changeSelectedButtonMenu(this->navDirection[2]);
				ButtonComponent::actionAlreadyCompute = true;
			}
			break;
		case GameMessage::DOWNMENU:
			if (this->buttonState == ButtonState::SELECTED && this->navDirection[3] != -1 && ButtonComponent::actionAlreadyCompute == false) {
				this->buttonState = ButtonState::CLASSIC;
				GameSystems::ObjectFactory::getInstance().changeSelectedButtonMenu(this->navDirection[3]);
				ButtonComponent::actionAlreadyCompute = true;
			}
			break;
		case GameMessage::SELECT_CONTROLLER_MENU:
			GameMessage::MenuControllerMessage *controllerMessage = (GameMessage::MenuControllerMessage *)message;
			if (this->buttonState == ButtonState::PLAYERCREATOR) {
				this->buttonState = ButtonState::CHOOSEPLAYER;
				this->idPad = controllerMessage->idController;
				createPlayer(controllerMessage->idController);
			}
			break;
		}
	}

	void ButtonComponent::toggleSelected(bool state) {
		if (this->actionName == "backPlayer" || this->actionName == "backLevel")
			return;
		if (this->buttonState == ButtonState::CLASSIC && state == true)
			this->buttonState = ButtonState::SELECTED;
		else if (this->buttonState == ButtonState::SELECTED && state == false)
			this->buttonState = ButtonState::CLASSIC;
	}

	void ButtonComponent::execAction()
	{
		if (this->actionName == "resumeToLevel" || this->actionName == "./config/menus/pause_return_main_menu.json")
			GameSystems::AudioSystem::_pauseMenu = false;
		if (this->specialFunction != "") {
			if (this->functionMap[this->specialFunction] != NULL)
				this->functionMap[this->specialFunction](this);
		} else {
			this->typeMap[this->buttonType](this);
		}
	}

	void ButtonComponent::createPlayer(int idController)
	{
		GameSystems::ObjectFactory::getInstance().addOrChangePlayerWithController(idController, this->numPlayerSelected);
		std::stringstream ss;
		ss << "./assets/sprite/menu/playerSelection" << this->numPlayerSelected << ".png";
		GameSystems::ObjectFactory::getInstance().changeGameObjectSpriteComponent(this->composition, ss.str());
	}

	void ButtonComponent::execMenu()
	{
		GameSystems::ObjectFactory::getInstance().LoadMenuFileAsCurrent(this->actionName);
	}

	void ButtonComponent::execLevel()
	{
		GameSystems::ObjectFactory::getInstance().LoadLevelFileAsCurrent(this->actionName);
	}

	void ButtonComponent::execFunction()
	{
		if (this->functionMap[this->actionName] != NULL)
			this->functionMap[this->actionName](this);
	}

	void ButtonComponent::changeResolution()
	{
		if (GameSystems::GraphicsSystem::Camera::getInstance().resolutionHeight == 720) {
			std::cout << "resolution change to 1080p" << std::endl;
			GameSystems::GraphicsSystem::Camera::getInstance().setResolution1080p();
		}
		else {
			std::cout << "resolution change to 720p" << std::endl;
			GameSystems::GraphicsSystem::Camera::getInstance().setResolution720p();
		}
	}

	void ButtonComponent::resumeToLevel()
	{
		std::cout << "resume" << std::endl;
		GameSystems::ObjectFactory::getInstance().stateGame = GameSystems::ObjectFactory::gameState::LEVEL;
	}

	void ButtonComponent::restartLevel()
	{
		std::cout << "resume" << std::endl;
		GameSystems::ObjectFactory::getInstance().LoadLevelFileAsCurrent(GameSystems::ObjectFactory::getInstance().currentLevelFileName);
	}

	void ButtonComponent::quitGame() {
		std::cout << "quit game" << std::endl;
		GameEngine::Core::gameLoop = false;
	}

	void ButtonComponent::prevMenu() {
		std::cout << "prev game" << std::endl;
		GameSystems::ObjectFactory::getInstance().returnPrevMenuOrResumeLevel();
	}

	void ButtonComponent::backPlayer() {
		GameSystems::ObjectFactory::getInstance().LoadMenuFileAsCurrent("./config/menus/main_menu.json");
	}

	void ButtonComponent::backLevel() {
		GameSystems::ObjectFactory::getInstance().LoadMenuFileAsCurrent("./config/menus/choose_nb_player_menu.json");
	}

	void ButtonComponent::backEditor() {
		GameSystems::ObjectFactory::getInstance().LoadMenuFileAsCurrent("./config/menus/editor_level_menu.json");
	}
	
	void ButtonComponent::switchFullScreen() {
		GameSystems::WindowInputSytem::fullscreen = !GameSystems::WindowInputSytem::fullscreen;
	}

	void ButtonComponent::startLevelEditor() {
		GameSystems::ObjectFactory::getInstance().LoadLevelEditor();
	}

	void ButtonComponent::loadLevelInEditor() {
		GameSystems::ObjectFactory::getInstance().LoadLevelEditorWithLevel(this->actionName);
	}

	void ButtonComponent::deleteLevel() {
		std::string filename = this->actionName.substr(this->actionName.find_last_of("/") + 1);
		filename = filename.substr(0, filename.find_last_of("."));
		std::cout << filename << std::endl;
		std::string previewFile = "./assets/levels_preview/" + filename + ".png";
		std::remove(previewFile.c_str());
		std::remove(this->actionName.c_str());
		GameSystems::ObjectFactory::getInstance().LoadMenuFileAsCurrent("./config/menus/delete_level_menu.json");
	}

}