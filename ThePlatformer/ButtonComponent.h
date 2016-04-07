#pragma once

#include "BaseComponent.h"
#include <map>
#include <functional>
#include "GraphicsSystem.h"
#include "ObjectFactory.h"
#include "MenuControllerMessage.h"
#include "WindowInputSytem.h"

namespace GameComponents {
	class ButtonComponent : public BaseComponent
	{
		enum ButtonType
		{
			MENU,
			LEVEL,
			FUNCTION,
		};
		enum ButtonState
		{
			CLASSIC,
			SELECTED,
			PLAYERCREATOR,
			CHOOSEPLAYER,
			READYPLAYER,
		};
		friend class GameSystems::ObjectFactory;

	public:
		~ButtonComponent();
		void setNav(GameTools::JsonValue & value);
		void setNav(int *values, int size);
		COMPONENT_TYPE getType() const;
		void Update(double dt);
		void drawSquare(GLfloat x, GLfloat y, GLfloat width, GLfloat height);
		void Init();
		void sendMessage(GameMessage::Message*);
		void toggleSelected(bool state);
		ButtonType buttonType;
		ButtonState buttonState;
		std::string actionName;
		void execAction();
		void createPlayer(int idController);
	private:
		ButtonComponent(GameObjects::BaseGameObject * object, const std::string & buttonType, const std::string & actionName);
		const COMPONENT_TYPE type = COMPONENT_TYPE::BUTTON;
		std::map<std::string, std::function<void(ButtonComponent*)>> functionMap;
		std::map<ButtonType, std::function<void(ButtonComponent*)>> typeMap;
		void execMenu();
		void execLevel();
		void execFunction();
		void changeResolution();
		void resumeToLevel();
		void restartLevel();
		void quitGame();
		void prevMenu();
		void backPlayer();
		void switchFullScreen();
		void startLevelEditor();
		int numPlayerSelected;
		int idPad;
		int *navDirection;
		static bool actionAlreadyCompute;
		bool movingButton;
		int numMovingButton;
		int sizeListMovingButton;
	};
}
