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
	class TextComponent : public BaseComponent
	{
		friend class GameSystems::ObjectFactory;
	public:
		virtual ~TextComponent();
		virtual COMPONENT_TYPE getType() const;
		virtual void Update(double);
		void drawText(std::string str, int posX, int posY, int size = 5);
		virtual void Update();
		virtual void Init();
		virtual void sendMessage(GameMessage::Message*);
	private:
		TextComponent(GameObjects::BaseGameObject*);
		const COMPONENT_TYPE type = COMPONENT_TYPE::TEXT;
		GameTools::SpriteSheet *sheet;

	};
}
