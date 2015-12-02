#include "ButtonComponent.h"

namespace GameComponents {

	bool ButtonComponent::actionAlreadyCompute = false;

	ButtonComponent::ButtonComponent(GameObjects::BaseGameObject* object, const std::string &buttonType, const std::string& actionName) : BaseComponent(object)
	{
		object->attachComponent(this);
		this->actionName = actionName;
		this->numPlayerSelected = 1;
		if (buttonType == "menu") { this->buttonType = ButtonType::MENU; }
		else if (buttonType == "level") { this->buttonType = ButtonType::LEVEL; }
		else if (buttonType == "function") { this->buttonType = ButtonType::FUNCTION; }

		this->typeMap[ButtonType::MENU] = &ButtonComponent::execMenu;
		this->typeMap[ButtonType::LEVEL] = &ButtonComponent::execLevel;
		this->typeMap[ButtonType::FUNCTION] = &ButtonComponent::execFunction;

		this->functionMap["changeResolution"] = &ButtonComponent::changeResolution;
		this->functionMap["resumeToLevel"] = &ButtonComponent::resumeToLevel;
		this->functionMap["restartLevel"] = &ButtonComponent::restartLevel;
		this->functionMap["quitGame"] = &ButtonComponent::quitGame;
		this->functionMap["prevMenu"] = &ButtonComponent::prevMenu;
		this->functionMap["backPlayer"] = &ButtonComponent::backPlayer;
		this->functionMap["switchFullScreen"] = &ButtonComponent::switchFullScreen;
		
		this->buttonState = ButtonState::CLASSIC;
		if (actionName == "createPlayer") {
			this->buttonState = ButtonState::PLAYERCREATOR;
			GameSystems::ObjectFactory::getInstance().clearPlayers();
		}
		this->navDirection = new int[4] { -1, -1, -1, -1 };
	}


	ButtonComponent::~ButtonComponent()
	{
	}

	void ButtonComponent::setNav(GameTools::JsonValue &value)
	{
		assert(value.getTag() == GameTools::JSON_ARRAY);
		int i = -1;
		for (auto j : value) {
			assert(i < 4);
			if (i == -1) {
				if ((int)j->value.toNumber() == 1)
					this->toggleSelected(true);
			}
			else {
				this->navDirection[i] = (int)j->value.toNumber();
			}
			i++;
		}
	}

	COMPONENT_TYPE ButtonComponent::getType()
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
		if (this->buttonState == ButtonState::SELECTED) {
			drawSquare(x, y, width, height);
		}
	}

	void ButtonComponent::drawSquare(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
		glLineWidth(3);
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_LINES);
		glVertex2f(x, y);
		glVertex2f(x + width, y);
		glEnd();

		//left
		glBegin(GL_LINES);
		glVertex2f(x, y);
		glVertex2f(x, y + height);
		glEnd();

		//right
		glBegin(GL_LINES);
		glVertex2f(x + width, y);
		glVertex2f(x + width, y + height);
		glEnd();

		//bottom
		glBegin(GL_LINES);
		glVertex2f(x, y + height);
		glVertex2f(x + width, y + height);
		glEnd();
	}

	void ButtonComponent::Init()
	{
	}

	void ButtonComponent::sendMessage(GameMessage::Message *message)
	{
		switch (message->id)
		{
		case GameMessage::CLICKON:
			this->execAction();
			break;
		case GameMessage::START_MENU:
			if (actionName == "resumeToLevel") {
				this->execAction();
			}
			break;
		case GameMessage::ECHAP_MENU:
			if (actionName == "resumeToLevel") {
				this->execAction();
			} else if (actionName == "backPlayer") {
				this->backPlayer();
			}
			break;
		case GameMessage::B_MENU:
			if (actionName == "backPlayer") {
				this->backPlayer();
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
			else if (this->buttonState == ButtonState::SELECTED)
			{
				this->execAction();
			}
			break;
		case GameMessage::LEFTMENU:
			if (this->buttonState == ButtonState::CHOOSEPLAYER) {
				this->numPlayerSelected--;
				if (this->numPlayerSelected < 1) {
					numPlayerSelected = 2;
				};
				createPlayer(this->idPad);
			}
			else if (this->buttonState == ButtonState::SELECTED && this->navDirection[0] != -1 && ButtonComponent::actionAlreadyCompute == false) {
				this->buttonState = ButtonState::CLASSIC;
				GameSystems::ObjectFactory::getInstance().changeSelectedButtonMenu(this->navDirection[0]);
				ButtonComponent::actionAlreadyCompute = true;
			}
			break;
		case GameMessage::RIGHTMENU:
			if (this->buttonState == ButtonState::CHOOSEPLAYER) {
				this->numPlayerSelected++;
				if (this->numPlayerSelected > 2) {
					numPlayerSelected = 1;
				};
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
		if (this->actionName == "backPlayer") {
			return;
		}
		if (this->buttonState == ButtonState::CLASSIC && state == true) {
			this->buttonState = ButtonState::SELECTED;
		}
		else if (this->buttonState == ButtonState::SELECTED && state == false) {
			this->buttonState = ButtonState::CLASSIC;
		}
	}

	void ButtonComponent::execAction()
	{
		this->typeMap[this->buttonType](this);
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
		if (this->functionMap[this->actionName] != NULL) {
			this->functionMap[this->actionName](this);
		}
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

	void ButtonComponent::switchFullScreen() {
		GameSystems::WindowInputSytem::fullscreen = !GameSystems::WindowInputSytem::fullscreen;
	}
}