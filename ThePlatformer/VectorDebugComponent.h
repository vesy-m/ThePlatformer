#pragma once

#include "BaseGameObject.h"

#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include "vectorMessage.h"
#include "debugManager.h"

namespace GameSystems {
	class ObjectFactory;
}

namespace GameComponents {

	class VectorDebugComponent : BaseComponent
	{
		friend class GameSystems::ObjectFactory;
	private:
		VectorDebugComponent(GameObjects::BaseGameObject*);
	public:
		
		~VectorDebugComponent();
		void sendMessage(GameMessage::Message*);
		COMPONENT_TYPE getType();
		void Update(double);
		void Init();
	private:
		const COMPONENT_TYPE type = COMPONENT_TYPE::DEBUGVECTOR;
		glm::vec2 velocity;
		bool showDebug;
	};

}