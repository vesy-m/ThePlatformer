#include "ButtonComponent.h"

namespace GameComponents {
	ButtonComponent::ButtonComponent(GameObjects::BaseGameObject* object, ButtonType buttonType, const std::string& actionName) : BaseComponent(object)
	{
		this->buttonType = buttonType;
		this->actionName = actionName;
		this->typeMap[ButtonType::MENU] = &ButtonComponent::execMenu;
		this->typeMap[ButtonType::LEVEL] = &ButtonComponent::execLevel;
		this->typeMap[ButtonType::FUNCTION] = &ButtonComponent::execFunction;

		this->functionMap["changeResolution"] = &ButtonComponent::changeResolution;
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
		this->functionMap[this->actionName](this);
	}

	void ButtonComponent::changeResolution()
	{
		GameSystems::GraphicsSystem::Camera::getInstance().setResolution1080p();
	}
}