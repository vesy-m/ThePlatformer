#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML\Window.hpp>
#include <map>
#include <sstream>
#include "JSONParser.h"
#include "BaseGameObject.h"
#include "debugManager.h"
#include "ObjectFactory.h"

namespace GameComponents {

	class InputComponent : public BaseComponent
	{	
	public:
		enum INPUT_TYPE
		{
			LEFT = 0,
			RIGHT = 1,
			JUMP = 2,
			FIRE = 3,
			SPECIAL = 4,
			DEBUG = 5,
			ROTATE_RIGHT = 6,
			ROTATE_LEFT = 7,
		};
		InputComponent(GameObjects::BaseGameObject *);
		virtual ~InputComponent();
		virtual COMPONENT_TYPE getType() { return WINDOW; }
		virtual GameObjects::BaseGameObject *getComposition();
		virtual void Update(double);

		virtual void UpdateInputState(sf::Event, double) = 0;
		virtual void Init() = 0;
		virtual void sendMessage(GameMessage::Message*) = 0;

		void setDuration(float);
		float getDuration();

	protected:
		std::map<INPUT_TYPE, bool> inputState;
		float duration;
	};
}