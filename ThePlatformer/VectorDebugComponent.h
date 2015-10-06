#pragma once

#include "BaseGameObject.h"

#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include "vectorMessage.h"

namespace GameComponents {

	class VectorDebugComponent : BaseComponent
	{
	public:
		VectorDebugComponent(GameObjects::BaseGameObject *);
		~VectorDebugComponent();
		void sendMessage(Message*);
		COMPONENT_TYPE getType();
		void Update();
		void Init();
	private:
		const COMPONENT_TYPE type = COMPONENT_TYPE::DEBUGVECTOR;
		glm::vec2 velocity;
		bool showDebug;
	};

}