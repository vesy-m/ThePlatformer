#pragma once

#include "BaseComponent.h"
#include "SpriteSheet.h"
#include <sstream>
#include <string>
#include "debugManager.h"

namespace GameSystems {
	class ObjectFactory;
}

namespace GameComponents {
	class TextComponent : BaseComponent
	{
		friend class GameSystems::ObjectFactory;
	public:
		~TextComponent();
		COMPONENT_TYPE getType();
		void Update(double dt);
		void Update();
		void Init();
		void sendMessage(GameMessage::Message*);
	private:
		TextComponent(GameObjects::BaseGameObject*);
		const COMPONENT_TYPE type = COMPONENT_TYPE::TEXT;
		SpriteSheet *sheet;

	};
}
