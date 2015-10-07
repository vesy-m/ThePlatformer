#pragma once

#include "BaseComponent.h"
#include "SpriteSheet.h"
#include <sstream>
#include <string>
#include "debugManager.h"

namespace GameComponents {

	class TextComponent : BaseComponent
	{
	public:
		TextComponent(GameObjects::BaseGameObject *object);
		~TextComponent();
		COMPONENT_TYPE getType();
		void Update(double dt);
		void Update();
		void Init();
		void sendMessage(Message*);
	private:
		const COMPONENT_TYPE type = COMPONENT_TYPE::TEXT;
		SpriteSheet *sheet;

	};
}
