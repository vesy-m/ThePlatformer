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
	class VectorDebugComponent : public BaseComponent
	{
		friend class GameSystems::ObjectFactory;
	private:
		VectorDebugComponent(GameObjects::BaseGameObject*);
	public:
		virtual ~VectorDebugComponent();
		virtual void sendMessage(GameMessage::Message*);
		virtual COMPONENT_TYPE getType();
		virtual void Update(double);
		virtual void Init();
	private:
		const COMPONENT_TYPE type = COMPONENT_TYPE::DEBUGVECTOR;
		glm::vec2 velocity;
		bool showDebug;
	};
}