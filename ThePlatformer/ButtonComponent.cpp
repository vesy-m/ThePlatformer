#include "ButtonComponent.h"

namespace GameComponents {
	ButtonComponent::ButtonComponent(GameObjects::BaseGameObject* object, ButtonType buttonType, const std::string& actionName) : BaseComponent(object)
	{
		object->attachComponent(this);
		this->buttonType = buttonType;
		this->actionName = actionName;
		this->typeMap[ButtonType::MENU] = &ButtonComponent::execMenu;
		this->typeMap[ButtonType::LEVEL] = &ButtonComponent::execLevel;
		this->typeMap[ButtonType::FUNCTION] = &ButtonComponent::execFunction;

		this->functionMap["changeResolution"] = &ButtonComponent::changeResolution;
		this->functionMap["resumeToLevel"] = &ButtonComponent::resumeToLevel;
		this->functionMap["restartLevel"] = &ButtonComponent::restartLevel;
	}


	ButtonComponent::~ButtonComponent()
	{
	}


	COMPONENT_TYPE ButtonComponent::getType()
	{
		return this->type;
	}

	void ButtonComponent::Update(double dt)
	{
	}

	void ButtonComponent::Init()
	{
	}

	void ButtonComponent::sendMessage(GameMessage::Message *message)
	{
		switch (message->id)
		{
		case GameMessage::Message::CLICKON:
			this->execAction();
			break;
		default:
			break;
		}
	}

	void ButtonComponent::execAction()
	{
		this->typeMap[this->buttonType](this);
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
}