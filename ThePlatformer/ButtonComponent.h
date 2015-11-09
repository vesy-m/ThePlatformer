#pragma once

#include "BaseComponent.h"
#include <map>
#include <functional>
#include "GraphicsSystem.h"
#include "ObjectFactory.h"

namespace GameComponents {
	class ButtonComponent : BaseComponent
	{
		enum ButtonType
		{
			MENU,
			LEVEL,
			FUNCTION,
		};
		friend class GameSystems::ObjectFactory;

	public:
		~ButtonComponent();
		COMPONENT_TYPE getType();
		void Update(double dt);
		void Init();
		void sendMessage(GameMessage::Message*);
		ButtonType buttonType;
		std::string actionName;
		void execAction();
	private:
		ButtonComponent(GameObjects::BaseGameObject* object, ButtonType buttonType, const std::string& actionName);
		const COMPONENT_TYPE type = COMPONENT_TYPE::BUTTON;
		std::map<std::string, std::function<void(ButtonComponent*)>> functionMap;
		std::map<ButtonType, std::function<void(ButtonComponent*)>> typeMap;
		void execMenu();
		void execLevel();
		void execFunction();
		void changeResolution();
		void resumeToLevel();
	};
}
