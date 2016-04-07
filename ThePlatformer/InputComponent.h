#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML\Window.hpp>
#include <map>
#include <sstream>
#include "JSONParser.h"
#include "BaseGameObject.h"
#include "GraphicsSystem.h"
#include "debugManager.h"
#include "AimMessage.h"
#include "ObjectFactory.h"

namespace GameComponents {

	enum CHEAT_CODE_TYPE
	{
		I_WIN,
		INVICIBLE,

		DEFAULT,
	};

	class InputComponent : public BaseComponent
	{	
	public:
		
		enum INPUT_TYPE
		{
			LEFT = 0,
			RIGHT = 1,
			JUMP = 2,
			ATTACK1 = 3,
			ATTACK2 = 4,
			ATTACK3 = 5,
			DEBUG = 6,
			ROTATE_RIGHT = 7,
			ROTATE_LEFT = 8,
		};

		InputComponent(GameObjects::BaseGameObject *, bool attachAsInput = true);
		virtual ~InputComponent();
		virtual COMPONENT_TYPE getType() const { return WINDOW; }
		virtual GameObjects::BaseGameObject *getComposition();
		virtual void Update(double);

		virtual void UpdateInputState(sf::Event, double) = 0;
		virtual void Init() = 0;
		virtual void sendMessage(GameMessage::Message*) = 0;

		void ParseCheatCodeFile(std::string cheatCodeFilename);
		CHEAT_CODE_TYPE IsCheatCodeActivated();
		void ExecuteCheatCode(CHEAT_CODE_TYPE);

		void setDuration(float);
		float getDuration();
		void setSavedDt(float);
		float getSavedDt();
		float getMaxElapsedTime();

	protected:
		std::map<INPUT_TYPE, bool> inputState;
		std::map<CHEAT_CODE_TYPE, std::vector<int>> cheatCodeMap;
		std::vector<int> savedMessage;

		std::string cheatCodeFilename;
		float duration;
		float savedDt;
		float maxElapsedTime;
	};
}